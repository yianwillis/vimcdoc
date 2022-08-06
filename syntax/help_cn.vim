" Vim syntax extention file for Chinese help
scriptencoding utf-8
" Language:	Vim help file
" Maintainer:	lang2 (http://vimcdoc.sf.net)
" Last Change:	2005 March
" Usage: copy this file to $VIMRUNTIME/syntax

syn match helpHeadlineCn	"^\([^\u0000-\u00ff]\|[A-Z]\)\(\s[^\u0000-\u00ff -.()_:]\|[A-Z0-9 ]\)*\ze\(\s\+\*\|$\)"
syn match helpSpecial		"CTRL-."
syn match helpVimCn		"VIM \(参考\|用户\)手册.*"
syn keyword helpNoteCn		注意 备注
syn match helpNoteCn		/注意\|备注\|警告/
syn match helpYizheCn		/译者/
syn region helpNotViCn		start="{没有" start="{仅" end="}" contains=helpLeadBlank,helpHyperTextJump

hi link helpHeadlineCn		helpHeadline
hi link helpVimCn		helpVim
hi link helpNoteCn		helpNote
hi link helpNotViCn		helpNotVi
hi link helpYizheCn		Identifier

" vim: ts=8 sw=2
