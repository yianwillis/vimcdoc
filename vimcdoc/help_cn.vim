" Vim syntax extention file for Chinese help
scriptencoding euc-cn
" Language:	Vim help file
" Maintainer:	lang2 (http://vimcdoc.sf.net)
" Last Change:	2005 March
" Usage: copy this file to $VIMRUNTIME/syntax


syn match helpVimCn		"VIM 参考手册.*"
syn match helpVimCn		"VIM 用户手册.*"
syn keyword helpNoteCn		注意 备注
syn keyword helpYizheCn		译者 译者：
"syn region helpNotVi		start="{Vi[: ]" start="{没有" start="{仅" end="}" contains=helpLeadBlank,helpHyperTextJump


hi link helpVimCn		Identifier
hi link helpNoteCn		Todo
hi link helpNotViCn		Special
hi link helpYizheCn		Identifier

" vim: ts=8 sw=2
