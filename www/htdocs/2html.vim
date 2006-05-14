" Vim syntax support file
" Maintainer: Bram Moolenaar <Bram@vim.org>
" Last Change: 2001 Dec 12
"	       (modified by David Ne\v{c}as (Yeti) <yeti@physics.muni.cz>)

" Transform a file into HTML, using the current syntax highlighting.

" Number lines when explicitely requested or when `number' is set
if exists("html_number_lines")
  let s:numblines = html_number_lines
else
  let s:numblines = &number
endif

" When not in gui we can only guess the colors.
if has("gui_running")
  let s:whatterm = "gui"
else
  let s:whatterm = "cterm"
  if &t_Co == 8
    let s:cterm_color0  = "#808080"
    let s:cterm_color1  = "#ff6060"
    let s:cterm_color2  = "#00ff00"
    let s:cterm_color3  = "#ffff00"
    let s:cterm_color4  = "#8080ff"
    let s:cterm_color5  = "#ff40ff"
    let s:cterm_color6  = "#00ffff"
    let s:cterm_color7  = "#ffffff"
  else
    let s:cterm_color0  = "#000000"
    let s:cterm_color1  = "#c00000"
    let s:cterm_color2  = "#008000"
    let s:cterm_color3  = "#804000"
    let s:cterm_color4  = "#0000c0"
    let s:cterm_color5  = "#c000c0"
    let s:cterm_color6  = "#008080"
    let s:cterm_color7  = "#c0c0c0"
    let s:cterm_color8  = "#808080"
    let s:cterm_color9  = "#ff6060"
    let s:cterm_color10 = "#00ff00"
    let s:cterm_color11 = "#ffff00"
    let s:cterm_color12 = "#8080ff"
    let s:cterm_color13 = "#ff40ff"
    let s:cterm_color14 = "#00ffff"
    let s:cterm_color15 = "#ffffff"
  endif
endif

" Return good color specification: in GUI no transformation is done, in
" terminal return RGB values of known colors and empty string on unknown
if s:whatterm == "gui"
  function! s:HtmlColor(color)
    return a:color
  endfun
else
  function! s:HtmlColor(color)
    if exists("s:cterm_color" . a:color)
      execute "return s:cterm_color" . a:color
    else
      return ""
    endif
  endfun
endif

if !exists("html_use_css")
  " Return opening HTML tag for given highlight id
  function! s:HtmlOpening(id)
    let a = ""
    if synIDattr(a:id, "inverse")
      " For inverse, we always must set both colors (and exchange them)
      let x = s:HtmlColor(synIDattr(a:id, "fg#", s:whatterm))
      let a = a . '<span style="background-color: ' . ( x != "" ? x : s:fgc ) . '">'
      let x = s:HtmlColor(synIDattr(a:id, "bg#", s:whatterm))
      let a = a . '<font color="' . ( x != "" ? x : s:bgc ) . '">'
    else
      let x = s:HtmlColor(synIDattr(a:id, "bg#", s:whatterm))
      if x != "" | let a = a . '<span style="background-color: ' . x . '">' | endif
      let x = s:HtmlColor(synIDattr(a:id, "fg#", s:whatterm))
      if x != "" | let a = a . '<font color="' . x . '">' | endif
    endif
    if synIDattr(a:id, "bold") | let a = a . "<b>" | endif
    if synIDattr(a:id, "italic") | let a = a . "<i>" | endif
    if synIDattr(a:id, "underline") | let a = a . "<u>" | endif
    return a
  endfun

  " Return closing HTML tag for given highlight id
  function s:HtmlClosing(id)
    let a = ""
    if synIDattr(a:id, "underline") | let a = a . "</u>" | endif
    if synIDattr(a:id, "italic") | let a = a . "</i>" | endif
    if synIDattr(a:id, "bold") | let a = a . "</b>" | endif
    if synIDattr(a:id, "inverse")
      let a = a . '</font></span>'
    else
      let x = s:HtmlColor(synIDattr(a:id, "fg#", s:whatterm))
      if x != "" | let a = a . '</font>' | endif
      let x = s:HtmlColor(synIDattr(a:id, "bg#", s:whatterm))
      if x != "" | let a = a . '</span>' | endif
    endif
    return a
  endfun
endif

" Return CSS style describing given highlight id (can be empty)
function! s:CSS1(id)
  let a = ""
  if synIDattr(a:id, "inverse")
    " For inverse, we always must set both colors (and exchange them)
    let x = s:HtmlColor(synIDattr(a:id, "bg#", s:whatterm))
    let a = a . "color: " . ( x != "" ? x : s:bgc ) . "; "
    let x = s:HtmlColor(synIDattr(a:id, "fg#", s:whatterm))
    let a = a . "background-color: " . ( x != "" ? x : s:fgc ) . "; "
  else
    let x = s:HtmlColor(synIDattr(a:id, "fg#", s:whatterm))
    if x != "" | let a = a . "color: " . x . "; " | endif
    let x = s:HtmlColor(synIDattr(a:id, "bg#", s:whatterm))
    if x != "" | let a = a . "background-color: " . x . "; " | endif
  endif
  if synIDattr(a:id, "bold") | let a = a . "font-weight: bold; " | endif
  if synIDattr(a:id, "italic") | let a = a . "font-style: italic; " | endif
  if synIDattr(a:id, "underline") | let a = a . "text-decoration: underline; " | endif
  return a
endfun

" Set some options to make it work faster.
" Expand tabs in original buffer to get 'tabstop' correctly used.
" Don't report changes for :substitute, there will be many of them.
let s:old_title = &title
let s:old_icon = &icon
let s:old_et = &l:et
let s:old_report = &report
set notitle noicon
setlocal et
set report=1000000

" Split window to create a buffer with the HTML file.
if expand("%") == ""
  new Untitled.html
else
  new %.html
endif
set modifiable
%d
let s:old_paste = &paste
set paste

" The DTD
if exists("html_use_css")
  exe "normal a<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"\n    \"http://www.w3.org/TR/html4/strict.dtd\">\n\e"
endif

" HTML header, with the title and generator ;-). Left free space for the CSS,
" to be filled at the end.
exe "normal a<html>\n<head>\n<title>\e"
exe "normal a" . expand("%:t:r") . "</title>\n\e"
exe "normal a<meta name=\"Generator\" content=\"Vim/" . version/100 . "." . version %100 . "\">\n\e"
if exists("html_use_css")
  exe "normal a<style type=\"text/css\">\n<!--\n-->\n</style>\n\e"
endif
exe "normal a</head>\n<body>\n<pre>\n\e"

exe "normal \<C-W>p"

" List of all id's
let s:idlist = ","

" Loop over all lines in the original text
let s:end = line("$")
let s:lnum = 1
while s:lnum <= s:end

  " Get the current line, with tabs expanded to spaces when needed
  " FIXME: What if it changes syntax highlighting?
  let s:line = getline(s:lnum)
  if stridx(s:line, "\t") >= 0
    exe s:lnum . "retab!"
    let s:did_retab = 1
    let s:line = getline(s:lnum)
  else
    let s:did_retab = 0
  endif
  let s:len = strlen(s:line)
  let s:new = ""

  if s:numblines
    let s:new = '<span class="lnr">' . strpart('        ', 0, strlen(line("$")) - strlen(s:lnum)) . s:lnum . '</span>  '
  endif

  " Loop over each character in the line
  let s:col = 1
  while s:col <= s:len
    let s:startcol = s:col " The start column for processing text
    let s:id = synID(s:lnum, s:col, 1)
    let s:col = s:col + 1
    " Speed loop (it's small - that's the trick)
    " Go along till we find a change in synID
    while s:col <= s:len && s:id == synID(s:lnum, s:col, 1) | let s:col = s:col + 1 | endwhile

    " Output the text with the same synID, with class set to c{s:id}
    let s:id = synIDtrans(s:id)
    let s:new = s:new . '<span class="c' . s:id . '">' . substitute(substitute(substitute(substitute(substitute(strpart(s:line, s:startcol - 1, s:col - s:startcol), '&', '\&amp;', 'g'), '<', '\&lt;', 'g'), '>', '\&gt;', 'g'), '"', '\&quot;', 'g'), "\x0c", '<hr class="PAGE-BREAK">', 'g') . '</span>'
    " Add the class to class list if it's not there yet
    if stridx(s:idlist, "," . s:id . ",") == -1
      let s:idlist = s:idlist . s:id . ","
    endif

    if s:col > s:len
      break
    endif
  endwhile
  if s:did_retab
    undo
  endif

  exe "normal \<C-W>pa" . strtrans(s:new) . "\n\e\<C-W>p"
  let s:lnum = s:lnum + 1
  +
endwhile
" Finish with the last line
exe "normal \<C-W>pa</pre>\n</body>\n</html>\e"

" Now, when we finally know which, we define the colors and styles
if exists("html_use_css")
  8
endif

" Find out the background and foreground color.
let s:fgc = s:HtmlColor(synIDattr(highlightID("Normal"), "fg#", s:whatterm))
let s:bgc = s:HtmlColor(synIDattr(highlightID("Normal"), "bg#", s:whatterm))
if s:fgc == ""
  let s:fgc = ( &background == "dark" ? "#ffffff" : "#000000" )
endif
if s:bgc == ""
  let s:bgc = ( &background == "dark" ? "#000000" : "#ffffff" )
endif

" Normal/global attributes
" For Netscape 4, set <body> attributes too, though, strictly speaking, it's
" incorrect.
if exists("html_use_css")
  execute "normal A\npre { color: " . s:fgc . "; background-color: " . s:bgc . "; }\e"
  yank
  put
  execute "normal ^cwbody\e"
else
  execute '%s:<body>:<body ' . 'bgcolor="' . s:bgc . '" text="' . s:fgc . '">'
endif

" Line numbering attributes
if s:numblines
  if exists("html_use_css")
    execute "normal A\n.lnr { " . s:CSS1(highlightID("LineNr")) . "}\e"
  else
    execute '%s+<span class="lnr">\([^<]*\)</span>+' . s:HtmlOpening(highlightID("LineNr")) . '\1' . s:HtmlClosing(highlightID("LineNr")) . '+g'
  endif
endif

" Gather attributes for all other classes
let s:idlist = strpart(s:idlist, 1)
while s:idlist != ""
  let s:attr = ""
  let s:col = stridx(s:idlist, ",")
  let s:id = strpart(s:idlist, 0, s:col)
  let s:idlist = strpart(s:idlist, s:col + 1)
  let s:attr = s:CSS1(s:id)
  " If the class has some attributes, export the style, otherwise DELETE all
  " its occurences to make the HTML shorter
  if s:attr != ""
    if exists("html_use_css")
      execute "normal A\n.c" . s:id . " { " . s:attr . "}"
    else
      execute '%s+<span class="c' . s:id . '">\([^<]*\)</span>+' . s:HtmlOpening(s:id) . '\1' . s:HtmlClosing(s:id) . '+g'
    endif
  else
    execute '%s+<span class="c' . s:id . '">\([^<]*\)</span>+\1+g'
    8
  endif
endwhile

" Cleanup (we've already lost last user's pattern match highlighting)
%s:\s\+$::e
if has("extra_search")
  nohlsearch
endif

" Restore old settings
let &report = s:old_report
let &title = s:old_title
let &icon = s:old_icon
let &paste = s:old_paste
exe "normal \<C-W>p"
let &l:et = s:old_et
exe "normal \<C-W>p"

" Save a little bit of memory (worths doing?)
unlet s:old_et s:old_paste s:old_icon s:old_report s:old_title
unlet s:whatterm s:idlist s:lnum s:end s:fgc s:bgc
unlet! s:col s:id s:attr s:len s:line s:new s:did_retab s:numblines
delfunc s:HtmlColor
delfunc s:CSS1
if !exists("html_use_css")
  delfunc s:HtmlOpening
  delfunc s:HtmlClosing
endif
