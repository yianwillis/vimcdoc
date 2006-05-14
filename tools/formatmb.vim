"								 Version 1.5
" format.vim -	Format multibyte text, for tha languages, which can split
"		line anywhere, unless prohibited. (for Vim 6.0 alpha)
"
" Last Change:	  12-Jan-2002.
" Maintainer:	  Muraoka Taro <koron@tka.att.ne.jp>
" Practised By:	  Takuhiro Nishioka <takuhiro@super.win.ne.jp>
" Base Idea:	  Muraoka Taro <koron@tka.att.ne.jp>
" Copyright:	  Public Domain
" Modified:	  Edward G.J. Lee <edt1023@speedymail.org> 2002.02.11
" 自行更改为 cp936 以适合简体中文

scriptencoding cp936

" function Format(start_line_number, end_line_number)
" 
" Format() will allow format multibyte text.  In some of East Asian
" languages, the line can break anywhere, unless prohibited.  Original Vim's
" "gq" format command doesn't allow to break line at the midst of word.
" This function split line at each multibyte character.  And it can handle
" prohibited line break rules.
"
" This function is following Vim's "gq" command. But there will be lack of
" something.

if exists('plugin_format_disable')
  finish
endif

"---------------------------------------------------------------------------
"				    Options
"
" "format_command"
"
" Specifies the format command that format lines to the width the
" 'textwidth' option specifies. The "Q" command formerly did this, so if you
" still want to use "Q", set this to "Q"
"
"let format_command = "Q"
if !exists('format_command')
  let format_command = "gq"
endif

"
" "format_join_spaces"
"
" Delete a space , when joining lines, according to the following rules.
" This rule is also applied to "J" command
"   1	line end with AND next line start with a multibyte char
"   2	line end with OR  next line start with a multibyte char
"   3	same with original join command
"
if !exists("g:format_join_spaces")
  let g:format_join_spaces = 1
endif

"
" "format_follow_taboo_rule"
"
" Move to a point that will not break forbidden line break rules. If you
" don't want to do this, set this to "0".
"
if !exists("g:format_follow_taboo_rule")
  let g:format_follow_taboo_rule = 1
endif

"
" "format_allow_over_tw"
"
" The width that can over 'textwidth'. This variable is used for taboo rule.
"
if !exists("g:format_allow_over_tw")
  let g:format_allow_over_tw = 2
endif

"
" "format_indent_sensitive"
"
" When the indentation changes, it's the end of a paragraph. Note that if
" this option is set, second indentation is disabled.
"
if !exists("g:format_indent_sensitive")
  let g:format_indent_sensitive = 0
endif

"---------------------------------------------------------------------------
"				  Sub Options
"
" "g:format_no_begin"
"
" This option is space-separated list of characters, that are forbidden to
" be at beginning of line. Add two spaces for ASCII characters. See also
" TabooRuleMatch()
let g:format_no_begin = "!  ,  .  ?  )  ]  }  -  _  ~  :  ;  ！  ，  。  ？  ）  ：  ；  "

"
" "g:format_no_end"
"
" This option is space-separated list of characters, that are forbidden to
" be at end of line. Add two spaces for ASCII characters. See also
" TabooRuleMatch()
"
let g:format_no_end = "(  [  {  "

"
" For Japanese.  There are encoding name aliases, so we cannot directly
" compare option 'encoding' with locale name (ex: 'japan').
"
"let s:save_encoding = &encoding
"let &encoding = 'japan'
"if &encoding == s:save_encoding
"  let no_b = ''
"  let no_b = no_b . "?? ?? ?f ?h ?? ?? ?? ?? ?A ?B ?X ?r ?t ?v ?x ?z ?l "
"  let no_b = no_b . "?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?J ?K ?T ?U "
"  let no_b = no_b . "?@ ?B ?D ?F ?H ?b ?? ?? ?? ?? ?? ?? "
"  let no_b = no_b . "?E ?[ ?R ?S ?I ?? ?j ?C ?D ?F ?G ?H ?n ?p ?c ?` "

"  let no_e = ''
"  let no_e = no_e . "?? ?e ?g ?q ?s ?u ?w ?y ?k ?? ?i ?m ?o ?? "

"  let g:format_no_begin = g:format_no_begin . no_b
"  let g:format_no_end = g:format_no_end . no_e
"  unlet no_b no_e
"endif
"let &encoding = s:save_encoding
"unlet s:save_encoding

"
" "s:format_motion_list"
"
" Specifiles the motion command that could follow "format_command". These
" are pairs of two letters. Note that not all motion commands can be
" specified here. Use visual mode for other motions.
"
let m_list = "apawaWasa]a[a)a(aba>a}a{aB"
let m_list = m_list . "ipiwiWisi]i[i)i(ibi>i}i{iB"
let m_list = m_list . "gqq "
let m_list = m_list . "h j k l 0 ^ $ ; , - + w W e E b B "
let m_list = m_list . "( ) { } n N % H M L G / ? "
let m_list = m_list . "gjgkggg0g^gmgegEg$]][[][[[[]''``"
let m_list = m_list . "'[`[']`]'<`<'>`>'\"`\""
let m_list = m_list . "[([{])]}]m]M[m[M[#]#[*[/"
let m_list = m_list . "'a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'u'v'w'x'y'z"
let m_list = m_list . "`a`b`c`d`e`f`g`h`i`j`k`l`m`n`o`p`q`r`s`t`u`v`w`x`y`z"
let m_list = m_list . "2j3j4j5j6j7j8j9j"
let m_list = m_list . "2k3k4k5k6k7k8k9k"
let m_list = m_list . "2H3H4H5H6H7H8H9H"
let m_list = m_list . "2L3L4L5L6L7L8L9L"
let s:format_motion_list = m_list
unlet m_list

"---------------------------------------------------------------------------
"
" DoMappings()
"   Do mappings.
"
function! DoMappings()
  " Normal mode mappings.
  let length = strlen(s:format_motion_list)
  let i = 0
  while i <= length - 2
    let motion = strpart(s:format_motion_list, i, 2)
    let motion = substitute(motion, " $", "", "")
    execute "nmap <silent> " . g:format_command . motion . " :call " . "<SID>FormatWorkhorse(\"" . motion . "\")<CR>"
    let i = i + 2
  endwhile

  " Visual mode mapping.
  execute "vmap <silent> ".g:format_command." <ESC>:call"." <SID>Format(line(\"'<\"), line(\"'>\"))<CR>"

  " Change "J" to follow "g:format_join_spaces"
  nmap <silent> J :call <SID>DoRangeJoin("")<CR>
  vmap <silent> J <ESC>:call <SID>DoJoinRange(line("'<"), line("'>"))<CR>
endfunction

"
" FormatWorkhorse(motion)
"   Select the area that moves over, then pass the start and end line number
"   of the area to Format()
"
function! s:FormatWorkhorse(motion)
  if a:motion == "gq" || a:motion == "q"
    execute "normal! V\<ESC>"
  elseif a:motion == "/" || a:motion == "?"
    execute "let pattern = input(\"" . a:motion . "\")"
    execute "normal! v" . a:motion . pattern . "\<CR>\<ESC>"
  else
    execute "normal! v" . a:motion . "\<ESC>"
  endif
  call s:Format(line("'<"), line("'>"))
endfunction

"
" Format(start_lnum, end_lnum)
"   Format the area from the start line number to the end line number.
"
function! s:Format(start_lnum, end_lnum)
  let count_nr = a:end_lnum - a:start_lnum + 1
  let advance = 1
  " current line is the start of a paragraph.
  let first_par_line = 1
  " the second indent
  let second_indent = "default"

  " Check 2 in the formatoptions
  let do_second_indent = s:HasFormatOptions('2')

  let showcmd_save = &showcmd
  set noshowcmd
  let wrap_save = &wrap
  set nowrap
  let lazyredraw_save = &lazyredraw
  set lazyredraw

  " Set cursor to the start line number.
  call s:SetCursor(a:start_lnum)

  " Get info about the previous and current line.
  if a:start_lnum == 1
    " current line is not part of paragraph
    let is_not_par = 1
  else
    normal! k
    " the commet leader of current line
    let leader = s:GetLeader()
    let is_not_par = s:FmtCheckPar(leader)
    normal! j
  endif

  " the commet leader of next line
  let next_leader = s:GetLeader()
  " next line not part of paragraph
  let next_is_not_par = s:FmtCheckPar(next_leader)

  " at end of paragraph
  let is_end_par = is_not_par || next_is_not_par

  " operation top
  let op_top = 1
  while count_nr > 0
    " Advance to next paragraph.
    if advance
      if op_top
	let op_top = 0
      else
	normal! j
      endif
      let leader = next_leader
      let is_not_par = next_is_not_par
      " previous line is end of paragraph
      let prev_is_end_par = is_end_par
    endif

    " The last line to be formatted.
    if count_nr == 1
      let next_leader = ""
      let next_is_not_par = 1
    else
      normal! j
      let next_leader = s:GetLeader()
      let next_is_not_par = s:FmtCheckPar(next_leader)
      normal! k
    endif

    let advance = 1
    let is_end_par = is_not_par || next_is_not_par

    " Skip lines that are not in a paragraph.
    if !is_not_par

      " For the first line of a paragraph, check indent of second line.
      " Don't do this for comments and empty lines.
      if first_par_line
	  \&& do_second_indent
	  \&& prev_is_end_par
	  \&& leader =~ "^\\s*$"
	  \&& next_leader =~ "^\\s*$"
	  \&& getline(line(".") + 1) !~ "^$"
	let second_indent = next_leader
      endif

      " When the comment leader changes, it's the end of the paragraph
      if !s:SameLeader(leader, next_leader)
	let is_end_par = 1
      endif

      " If we have got to the end of a paragraph, format it.
      if is_end_par
	" do the formatting
	call s:FormatLine(second_indent)
	let second_indent = "default"
	let first_par_line = 1
      endif

      " When still in same paragraph, join the lines together.
      if !is_end_par
	let advance = 0
	" join current line and next line without the comment leader
	call s:DoJoin(next_leader)
	let first_par_line = 0
      endif

    endif
    let count_nr = count_nr - 1
  endwhile
  if wrap_save
    set wrap
  endif
  if !lazyredraw_save
    set nolazyredraw
  endif
  if showcmd_save
    set showcmd
  endif
endfunction

"
" FormatLine(second_indent)
"   Format currentline.
"
function! s:FormatLine(second_indent)
  " check textwidth
  if &textwidth == 0
    let textwidth = 76
  else
    let textwidth = &textwidth
  endif

  let do_second_indent = s:HasFormatOptions("2")
  let fo_do_comments = s:HasFormatOptions("q")
  let second_indent = a:second_indent

  " save the original option's value
  let formatoptions_save = &formatoptions
  let iskeyword_save = &iskeyword

  let leader_width = s:GetLeader("get_leader_width")

  " When fo_do_comments is TRUE, set formatoptions value so that the comment
  " leader is set for next line.
  if fo_do_comments
    set formatoptions+=r
  else
    set formatoptions-=r
  endif

  " Set iskeyword option value to every printable ascii characters, so that
  " "w" can stop at only multibyte-ascii boundary or white space.
  set iskeyword="!-~"

  call s:SetCursor(line("."), textwidth)
  while s:GetWidth() > virtcol(".")
    let finish_format = 0
    let force_fold = 0
    let do_insert = 0
    let max_width = virtcol(".") + g:format_allow_over_tw

    let ch = s:GetCharUnderCursor()
    normal! l
    let next_ch = s:GetCharUnderCursor()
    normal! h

    " English word folding
    if ch =~ "[!-~]\\{1}" && next_ch =~ "[!-~]\\{1}"
      call s:MoveToWordBegin()
      if virtcol(".") - 1 > leader_width
	" move to previous word end
	normal! ge
      endif
    endif

    " Skip white spaces
    if ch =~ "\\s"
      while ch =~ "\\s" && virtcol(".") - 1 > leader_width
	normal! h
	let ch = s:GetCharUnderCursor()
      endwhile
      let force_fold = 1
    endif

    if virtcol(".") - 1 <= leader_width
      call s:MoveToFirstWordEnd(leader_width)
      let force_fold = 1
      if s:GetWidth() == virtcol(".")
	let finish_format = 1
      endif
    endif

    " Taboo rule
    if !finish_format && !force_fold && g:format_follow_taboo_rule
      normal! l
      let next_ch = s:GetCharUnderCursor()
      normal! h
      if s:TabooRuleMatch(g:format_no_begin, next_ch)
	normal! l
	while s:TabooRuleMatch(g:format_no_begin, next_ch)
	  " if cursor is at the line end, break.
	  if s:GetWidth() == virtcol(".")
	    let finish_format = 1
	    break
	  endif
	  normal! l
	  let next_ch = s:GetCharUnderCursor()
	endwhile
	if !finish_format
	  normal! h
	endif
      endif

      let ch = s:GetCharUnderCursor()
      if virtcol(".") > max_width
	let finish_format = 0
	while s:TabooRuleMatch(g:format_no_begin, ch)
	    \&& virtcol(".") - 1 > leader_width
	  normal! h
	  let ch = s:GetCharUnderCursor()
	endwhile
	if ch =~ "[!-~]\\{1}"
	  call s:MoveToWordBegin()
	  if virtcol(".") - 1 > leader_width
	    normal! ge
	  else
	    call s:MoveToFirstWordEnd(leader_width)
	    let force_fold = 1
	  endif
	else
	  let do_insert = 1
	endif
      endif

      let ch = s:GetCharUnderCursor()
      if s:TabooRuleMatch(g:format_no_end, ch) && !force_fold
	let do_insert = 0
	while s:TabooRuleMatch(g:format_no_end, ch)
	    \&& virtcol(".") -1 > leader_width
	  normal! h
	  let ch = s:GetCharUnderCursor()
	endwhile
	if virtcol(".") -1 <= leader_width
	  call s:MoveToFirstWordEnd(leader_width)
	endif
      endif
    endif

    if finish_format
      break
    endif

    if do_insert
      call s:InsertNewLine()
    else
      call s:AppendNewLine()
    endif

    if do_second_indent && second_indent != "default"
      call setline(line(".")
	  \, second_indent . substitute(getline("."), "^\\s*", "", ""))
      let do_second_indent = 0
      if strlen(second_indent) > 0
	normal! h
      endif
    endif

    if virtcol(".") == 1
      let leader_width = 0
    else
      let leader_width = virtcol(".")
    endif

    call s:SetCursor(line("."), textwidth)
  endwhile

  execute "set formatoptions=" . formatoptions_save
  execute "set iskeyword=" . iskeyword_save
endfunction

"
" GetLeader(...)
"   Get the comment leader string from current line. If argument
"   is specified, then return the comment leader width. Note that
"   returned comment leader and the current line's comment leader is
"   not always same.
"
function! s:GetLeader(...)
  if !s:HasFormatOptions('q')
    if a:0 == 1
      return 0
    endif
    return ""
  endif

  let col_save = virtcol(".")

  let formatoptions_save = &formatoptions
  let autoindent_save = &autoindent
  let cindent_save = &cindent
  let smartindent_save = &smartindent
  set formatoptions+=o
  set autoindent
  set nocindent
  set nosmartindent

  execute "normal! ox\<ESC>\"_x"

  if a:0 == 1
    if getline(".") =~ "^$"
      let leader_width = 0
    else
      let leader_width = virtcol(".")
    endif
  endif

  let leader = getline(".")

  if line(".") == line("$")
    normal! "_dd
  else
    normal! "_ddk
  endif

  execute "set formatoptions=" . formatoptions_save
  if !autoindent_save
    set noautoindent
  endif
  if cindent_save
    set cindent
  endif
  if smartindent_save
    set smartindent
  endif

  execute "normal! " . col_save . "|"

  if a:0 == 1
    return leader_width
  else
    return leader
  endif
endfunction

"
" FmtCheckPar(leader)
"   Blank lines, lines containing only white space or the comment leader,
"   are left untouched by the formatting. The function returns true in this
"   case.
"
function! s:FmtCheckPar(leader)
  let three_start = substitute(&com, '.*s[^:]*:\([^,]*\),.*', '\1', '')
  let three_end = substitute(&com, '.*e[^:]*:\([^,]*\),.*', '\1', '')
  let line = substitute(getline("."), "\\s*$", "", "")
  let line = substitute(line, "^\\s*", "", "")
  let leader = substitute(a:leader, "\\s*$", "", "")
  let leader = substitute(leader, "^\\s*", "", "")
  if line == three_start || line == three_end
    return 1
  endif
  return line == leader
endfunction

"
" SameLeader(leader1, leader2)
"   Return true if the two comment leaders given are the same. White-space is
"   ignored.
"
function! s:SameLeader(leader1, leader2)
  if g:format_indent_sensitive
    return a:leader1 == a:leader2
  else
    return substitute(a:leader1, "\\s\\+$", "", "")
	\== substitute(a:leader2, "\\s\\+$", "", "")
  endif
endfunction


"
" SetCursor(lnum, width)
"   Set cursor to the line number, then move the cursor to within the width
"   and the most right virtual column.
"
function! s:SetCursor(lnum, ...)
  execute a:lnum

  if a:0 == 1
    execute "normal! " . a:1 . "|"
    if a:1 > 2 && virtcol(".") > a:1
      normal! h
    endif
  endif
endfunction

"
" HasFormatOptions(x)
"   Return true if format option 'x' is in effect. Take care of no
"   formatting when 'paste' is set.
"
function! s:HasFormatOptions(x)
  if &paste
      \|| (a:x == "2" && !&autoindent)
      \|| (a:x == "2" && g:format_indent_sensitive)
    return 0
  endif
  return &formatoptions =~ a:x
endfunction

"
" DoRangeJoin(next_leader)
"   DoJoin driver, able to support range.
"
function! s:DoRangeJoin(next_leader) range
  if  count > 2
    let repeat = count - 1
  else
    let repeat = 1
  endif

  while repeat
    call s:DoJoin(a:next_leader)
    let repeat = repeat - 1
  endwhile
endfunction

"
" DoJoin(next_leader)
"   Join line and next line ,according to g:format_join_spaces. The comment
"   leader will be removed.
"
function! s:DoJoin(next_leader)
  if line(".") == line("$")
    return
  endif

  let showcmd_save = &showcmd
  set noshowcmd
  let wrap_save = &wrap
  set nowrap
  let lazyredraw_save = &lazyredraw
  set lazyredraw


  normal! $
  let end_char = s:GetCharUnderCursor()

  if s:HasFormatOptions("q") && a:next_leader != ""
    let next_leader = escape(a:next_leader, '^.*\$~[]')
    let next_leader = "^" . substitute(next_leader, "\\s*$", "", "")
    normal! j0
    if getline(".") =~ next_leader
      call setline(line("."), substitute(getline("."), next_leader, "", ""))
    else
      let leader_width = s:GetLeader("get_leader_width")
      let i = leader_width + 1
      execute "normal! 0\"_d" . i . "|"
    endif
    normal! k
  endif

  normal! J

  if s:GetWidth() > virtcol(".") && s:GetCharUnderCursor() == " "
    normal! l
    let begin_char = s:GetCharUnderCursor()
    normal! h
    if g:format_join_spaces == 1
	\&& (strlen(end_char) > 1 && strlen(begin_char) > 1)
      normal! "_x
    elseif g:format_join_spaces == 2
	\&& (strlen(end_char) > 1 || strlen(begin_char) > 1)
      normal! "_x
    endif
  endif
  if wrap_save
    set wrap
  endif
  if !lazyredraw_save
    set nolazyredraw
  endif
  if showcmd_save
    set showcmd
  endif
endfunction

"
" DoJoinRange(start_lnum, end_lnum)
"   Join lines from start_lnum to end_lnum, according to the
"   "$fomrat_join_spaces"
"
function! s:DoJoinRange(start_lnum, end_lnum)
  let count_nr = a:end_lnum - a:start_lnum
  call s:SetCursor(a:start_lnum)
  while count_nr > 0
    call s:DoJoin("")
    let count_nr = count_nr - 1
  endwhile
endfunction

"
" GetWidth()
"   Return the current line width. If the line is empty returns 0. Note that
"   if the character at the line end is a multibyte character, this returns
"   real width minus 1, same as virtcol().
"
function! s:GetWidth()
  return virtcol("$") - 1
endfunction

"
" GetCharUnderCursor()
"   Get (multibyte) character under current cursor.
"
function! s:GetCharUnderCursor()
  let str = getline(".")
  let idx = col(".") - 1
  let ch = str[idx]
  if char2nr(ch) >= 128
    return strpart(str, idx, 2)
  else
    return ch
  endif
endfunction

"
" AppendNewLine()
"   Insert newline after cursor.
"
function! s:AppendNewLine()
  execute "normal! a\<CR>\<ESC>"
endfunction

"
" InsertNewLine()
"   Insert newline before cursor.
"
function! s:InsertNewLine()
  execute "normal! i\<CR>\<ESC>"
endfunction

"
" MoveToWordEnd()
"   Move to the word end.
"
function! s:MoveToWordEnd()
  if line(".") == 1
    normal! wge
  else
    normal! gee
  endif
endfunction

"
" MoveToWordBegin()
"   Move to the word begin.
"
function! s:MoveToWordBegin()
  if line(".") == 1
    normal! wb
  else
    normal! gew
  endif
endfunction

"
" MoveToFirstWordEnd()
"   Move to the first word end after the comment leader.
"
function! s:MoveToFirstWordEnd(leader_width)
  let i = a:leader_width + 1
  execute "normal! " . i . "|"
  call s:MoveToWordEnd()
endfunction

"
" TabooRuleMatch(taboo_rule_list, char)
"   Return true when the character matches one of taboo_rule_list
"
function! s:TabooRuleMatch(taboo_rule_list, char)
  " add spaces to char so to match exactly one of the list
  if strlen(a:char) > 1
    let ch = a:char . " "
  else
    let ch = a:char . "  "
  endif

  " escape the special character
  return a:taboo_rule_list =~ escape(ch, '^.*\$~[]')
endfunction

call DoMappings()

" vi:set ts=8 sts=2 sw=2 tw=0:
