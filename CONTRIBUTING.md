VIMCDOC TRANSLATION GUIDE
=======

本文件用来作为一个翻译文档时的指南。包括必须统一的条目以及参考。任何意见和建议
请和 Willis (yianwillis@gmail.com) 联系。

https://github.com/yianwillis/vimcdoc

==============================================================================
# 强 制 规 则

1. 不能改动原文件的格式！不能改变各文本的颜色！请打开语法高亮，并使用

   ```vim
   :syntax on
   :set list
   :set listchars=tab:>-,trail:-
   ```
   命令来显示所有的字符用来帮助排板。
   同时，VIM 在帮助文件中使用了很多标记字符，用来帮助语法高亮。

   ```vim
   :hi Ignore guifg=color
   :hi Ignore ctermfg=color
   ```
   可显示这些隐藏字符 (请使用比较醒目的色彩代替 color)。

2. 一些 VIM 的专用术语必须统一。见下。

3. 如果不熟悉 VIM 帮助: 在 | | * * < > 等等之间的文本是 vim 用来建立超链的。
   不用翻译。

4. 各文件之间的衔接: VIM 文档各文件之间互相参阅, 例如在每个 usr_??.txt 的最后都
   将给出前后的文件主题, 翻译时请参考已经存在的文件, 以确保各个文件中的说法一致。

5. 所有文档应当使用 unix 行结束符。

   ```vim
   :set ff=unix
   ```

6. 当在 Vim 文档中出现全大写字母以表示某节的开始时，在翻译的中文字之间加入空
   格。例如：

   ```
	DELETING VARIABLES
   =>
	删 除 变 量
   ```

7. 行宽: Vim 帮助文件有固定的行宽--78，对于英文文本，Vim 可以自动排版，可是这对
   中文文本无效。所以，请在翻译时注意手动调整行宽，不要超过78。

8. 编码：所有翻译后的文本使用 UTF-8 编码。为保持最大兼容性，请在翻译完文档后，
   运行以下命令确保帮助文档能在 enc=euc-cn 环境下查看。

   ```shell
   $ iconv -f utf-8 -t euc-cn file.txt >/dev/null
   ```

9. 翻译日期：每个文档的第一行均有一个 Last Change: 翻译为 "最近更新"，然后使用
   译文的更新日期。

10. 标点符号不能出现在行首。对引号一律使用 *英文引号*。

11. 关于 note, Note 的翻译：视情况而定，可译为 "注意" 或 "备注"，之后_必须_
    是英文 ':' 或空格。以便 Vim 正确地分割 keyword。

# 术 语 译 法

下表列出了 Vim 文档中使用的术语及其对应的中文译法。本表内容会不断更新，欢迎提出
修改建议！

注意：本表供 Vim 中使用。

|    ENGLISH                     |       中文                     |
|--------------------------------|--------------------------------|
| Block                          | 大块 (如 aB 命令)              |
| Ex                             | Ex                             |
| GUI                            | GUI                            |
| Plugin                         | 插件                           |
| TABSTOP                        | 制表位                         |
| WORD                           | 字串                           |
| Win32                          | Win32                          |
| Windows                        | Windows                        |
| abandon                        | 放弃                           |
| abbreviations                  | 缩写                           |
| active                         | 活动的                         |
| alternate file                 | 轮换文件                       |
| append                         | 添加                           |
| arg                            | 参数                           |
| argument                       | 参数                           |
| atom                           | 原子                           |
| autocommand                    | 自动命令                       |
| backslash                      | 反斜杠                         |
| binary search                  | 二分法查找                     |
| blob                           | blob                           |
| block                          | 块                             |
| boolean                        | 布尔                           |
| brace                          | 括号                           |
| bracket                        | 方括号                         |
| break                          | 打断 (撤销序列)                |
| buffer                         | 缓冲区                         |
| channel                        | 通道                           |
| character set                  | 字符集                         |
| character-wise                 | 字符级                         |
| closure                        | 闭包                           |
| cluster                        | 簇                             |
| column                         | 列                             |
| combining/composing character  | 组合字符 (阿拉伯等语言)        |
| comment                        | 注释                           |
| completion, complete           | 补全                           |
| console                        | 控制台                         |
| copy                           | 复制                           |
| count                          | 计数 (普通命令前缀)            |
| cursor                         | 光标                           | 
| cut                            | 剪切                           |
| debugger                       | 调试器                         |
| diff                           | 比较                           |
| digraph                        | 二合字母                       |
| double-width (character)       | 双宽 (字符)                    |
| dump                           | 转储                           |
| emoji                          | 表情符号                       |
| encoding                       | 编码                           |
| encryption                     | 加密                           |
| event                          | 事件                           |
| exclusive                      | 开的 (动作类型)                |
| exception                      | 异常                           |
| expression                     | 表达式                         |
| farsi                          | 波斯语                         |
| feature                        | 特性                           |
| filter                         | 过滤                           |
| flag                           | 标志位                         |
| folding                        | 折叠                           |
| fontset                        | 字体集                         |
| format                         | 格式化 (程序) 排版 (普通文本)  |
| global identifier              | 全局标识符                     |
| hebrew                         | 希伯来语                       |
| home directory                 | (用户) 主目录                  |
| identifier                     | 标识符                         |
| included file                  | 头文件 (C/C++) 包含文件 (其他) |
| inclusive                      | 闭的 (动作类型)                |
| indent                         | 缩进                           |
| inner                          | 内                             |
| job                            | 作业                           |
| join                           | 连接                           |
| key mapping                    | 键盘映射                       |
| keymap                         | 键盘映射表                     |
| keyword                        | 关键字                         |
| lambda                         | 匿名函数                       |
| layout                         | 布局                           |
| like                           | 如                             |
| line break                     | 换行                           |
| linewise                       | 行级                           |
| literally                      | 按本义出现的，按字面意思的     |
| local identifier               | 局部标识符                     |
| locale                         | locale                         |
| man page                       | man page                       |
| mark                           | 位置标记                       |
| marker                         | 标志 (折叠)                    |
| matching                       | 匹配                           |
| modeless selection             | 无模式选择                     |
| modeline                       | 模式行                         |
| normal mode                    | 普通模式                       |
| notation                       | 记法，标记法                   |
| offset                         | 偏移                           |
| operator                       | 操作符                         |
| operator-pending mode          | 操作符等待模式                 |
| package                        | 软件包                         |
| paragraph                      | 段落                           |
| partial                        | 偏函数、偏函                   |
| paste                          | 粘贴                           |
| pattern                        | 模式                           |
| popup                          | 弹出窗口、弹窗                 |
| popup menu                     | 弹出菜单                       |
| portable                       | 可移植的                       |
| put                            | 放置                           |
| quickfix                       | 快速修复                       |
| redo                           | 重做 (undo 之反)               |
| regexp                         | 正则表达式                     |
| register                       | 寄存器                         |
| repeat                         | 重复                           |
| replace mode                   | 替换模式                       |
| reset                          | 复位                           |
| right-to-left                  | 从右到左                       |
| ruler                          | 标尺                           |
| sandbox                        | 沙盘                           |
| scope                          | 作用域                         |
| scroll                         | 滚屏                           |
| section                        | 小节                           |
| sentence                       | 句子                           |
| session                        | 会话                           |
| set                            | 置位 (布尔选项) 设置 (其他类型)|
| shaping                        | (字型) 重整                    |
| shell                          | 外壳                           |
| shell script                   | 外壳脚本                       |
| shiftwidth                     | shiftwidth                     |
| socket                         | 套接字                         |
| source (script)                | 执行或载入 (取决于语义)        |
| substitute                     | 替代 (专指 :s 命令)            |
| suspend                        | 挂起                           |
| swap file                      | 交换文件                       |
| syntax highlight               | 语法高亮                       |
| tabstop                        | 制表位                         |
| tag                            | 标签                           |
| text object                    | 文本对象                       |
| thesaurus                      | 同义词字典                     |
| timer                          | 定时器                         |
| timestamp                      | 时间戳                         |
| toolbar                        | 工具条                         |
| tooltip                        | 提示                           |
| undo                           | 撤销                           |
| verbose                        | 详细                           |
| view                           | 视图                           |
| virtual replace mode           | 虚拟替换模式                   |
| visual block                   | 可视列块                       |
| visual mode                    | 可视模式                       |
| widget                         | 窗口组件                       |
| word                           | 单词                           |
| word processor                 | 字处理器                       |
| wrap                           | 回绕                           |
| yank                           | 抽出                           |

==============================================================================
# 推 荐 规 则

1. 译者: 译者可将自己名字 (呢称、用户名均可) 置于文件中原文作者的名字下面一行。
   格式为 译者: (英文标点) 名字。但应同时给出本项目网址:
   http://github.com/yianwillis/vimcdoc

2. 这个项目翻译的目标是 Vim 最新版本文档，如果还在使用较老的版本，请到 Vim 主页
   下载，不然文档中介绍新功能可能不适用。
   注意: 非 Vim 官方发行的 plugin 的文档目前不在翻译之列。

3. 标点符号：建议在不改变原文的意思前提下 "尽量" 使用中文标点。有些地方的标点有
   特殊的功能，不能翻译为中文。例如正则模式中的 '.'

4. 中英文混合：因为英文本身带有空格，而中文没有，建议在混合中英文时加入空格。如
   同上面条目 2 中提到 Vim 的名字时。这样比较清楚。

==============================================================================
# man 文 件 更 新 步 骤

1. 导入原版 man 文件到翻译文件
   - （如果已执行过此导入步骤，则无需此操作。）
   - 从 Vim 源代码文件的 `runtime/doc/` 目录，将原文 man 文件复制到中文翻译工作
     仓库。
   ```shell
   $ cd </path/to/vim>/runtime/doc
   $ for file in evim.1 vim.1 vimdiff.1 vimtutor.1 xxd.1; do
       cp $file </path/to/lang-zh_CN>/runtime/doc/"${file%.1}-zh_CN.UTF-8.1"
     done
   $
   ```

2. 翻译
   - 查看原文的差异，同时更新翻译文件。
   ```shell
   $ git diff | gvim -R -
   ```

3. 显示确认
   - 可以通过以下命令确认显示效果。
   ```shell
   $ groff -Tutf8 -Dutf8 -mandoc -mzh vim-zh_CN.UTF-8.1 | less -R
   ```
