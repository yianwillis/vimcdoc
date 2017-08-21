vimcdoc
=======

Vim 中文文档计划

# 关 于

Vim (http://www.vim.org) 是一个功能非常强大，且具有很强扩展性的编辑器。而且 Vim
本身带有一个完备的帮助系统。本项目的目的就是将 Vim 的这些文档翻译成中文，以便更
多的人认识及更好地使用这个非常强大的编辑器。文档分成用户手册和参考手册两部分，
你既可以象使用教程那样循序渐进，也可以快速地查阅来获取帮助。

# 下 载

https://github.com/yianwillis/vimcdoc/releases 提供发布版本的下载。

* PDF 用户手册和参考手册
* tar.gz 包
* Win32 GB2312 版本和 UTF8 版本的中文自动安装程序

# 安装

## Vim 8.0 自带软件包支持

```shell
$ mkdir -p ~/.vim/pack/foo/start
$ cd ~/.vim/pack/foo/start
$ git clone git://github.com/yianwillis/vimcdoc.git
```

重启 Vim。

其中 foo 可以是任何你自选的名字。

当然，如果不想用 git，也可用解压下载的 tar.gz 包到 `~/.vim/pack/foo/start`。git
方式的好处可以随时进行更新。

## Vundle

.vimrc 中加入：

```
Plugin "yianwillis/vimcdoc"
```

重启 Vim 后执行 `:PluginInstall`。

## NeoBundle

.vimrc 中加入：

```
NeoBundle 'yianwillis/vimcdoc"
```

重启 Vim 后执行命令 `:NeoBundleInstall`。

## Pathogen

```shell
$ cd ~/.vim/bundle
$ git clone git://github.com/yianwillis/vimcdoc.git
```

重启 Vim。

## vim-plug

.vimrc 中加入:

```
Plug 'yianwillis/vimcdoc'
```

重启 Vim 后执行命令 `:PlugInstall`。

## Linux 程序安装

下载的 tar.gz 包括所有翻译过的 vim 文档 (.cnx 文件) 和相关的语法文件和插件。
先将其解压缩：

```shell
$ tar zxvf vimcdoc-<version>.tar.gz
```

然后进入 vimcdoc-<version> 目录并执行

```shell
$ ./vimcdoc.sh -i
```

就可以了。该安装程序会自动识别 Vim 的安装路径，将中文的文档拷贝到相应的地方。原
有的英文文档不受影响。

缺省安装 vimcdoc.vim 插件，设置缺省帮助语言为中文。如果你不希望如此，可用

```shell
$ ./vimcdoc.sh -I
```

来代替。

这种方法对 root 和非 root 用户都适用。但建议以 root 身份安装。当以 root 身份安
装时，文件会被拷贝至 /usr/share/vim/vimfiles/doc 下。因此所有系统的用户都可以使
用中文文档。如果你的 vim 是安装在 /usr/local 下的话，你需要这样设定 vim 的
runtimepath 选项：

```vim
:set rtp+=/usr/share/vim/vimfiles
```

你可以将上面的设定加入到你的 vimrc 文件中以便每次启动 vim 都生效。当以普通用户
安装时，所有文件会被拷贝至 ~/.vim/doc 下，所以仅对该用户有效。

## Win32 程序安装

建议使用已经做好的自动安装程序。该程序不写注册表，不建立程序组，不覆盖任何 Vim
原有文件。所以可以放心使用。

## 手动安装

你也可以自己动手来安装：只要把所有的中文文档以及 tags-cn 文件拷贝到 runtimepath
之一的 doc 子目录下就行了。runtimepath 可用在 vim 内用 `:set rtp?` 命令来得到。比
如在 `vimcdoc-<version>` 目录中，可以执行以下命令：

```shell
$ cp -R doc /usr/share/vim/vimfiles/doc
```

这种方法对 Linux 和 Win32 都有效。

现在启动 vim/gvim, 键入 :help 看看吧！


# 卸 载

## Linux 程序安装
如果你是使用的自动安装脚本安装的话，只要运行：

```shell
$ ./vimcdoc.sh -u
```

即可。但必须用与安装时同样的用户名 (root 用户安装程序会在
/usr/share/doc/vimcdoc 下安装该文件)。

## Win32 程序安装

假定你的 Vim 安装在 c:\vim 下，在 c:\vim\vimfiles\doc\ 目录内会有一个
vimcdoc-Uninst.exe，只要执行它就可以了。

## 设 置

你的 'encoding' 设置及字体必须支持中文显示。对于使用非 utf-8 中文环境的用户，在
浏览某些帮助文件的时候可能会遇到麻烦。这是因为那些文件包含无法在 gbk, gb2312 等
编码方式下显示的字符。遇到这种情况，有以下几种解决方案：

1. 使用 utf-8 中文环境。例如，将 `LC_ALL` 设定为 `zh_CN.UTF-8`
2. 强制 vim 使用 utf-8 编码。做法是 `:set enc=utf-8`
3. 如果你的系统有 GB18030 支持，可以让 vim 使用 GB18030 编码，因为 GB18030 对非
   中文字符也能进行适当的处理。方法是

   ```vim
   :set enc=2byte-gb18030
   ```

   这时，Vim 会正确地进行转换。注意这里不能通过设置 `LC_ALL` 来完成。

如果使用 2 或 3，建议把 vim 设置写入你的个人 .vimrc 设置文件，避免每次都要输入
命令的麻烦。

备注：如果 `set enc=utf-8` 时，使用的中文消息出现乱码，可以同时设置

```vim
:language message zh_CN.UTF-8
```

# 在 线 阅 读

可在线阅读帮助文档的 HTML 版。

http://yianwillis.github.io/vimcdoc/

为了最佳阅读效果，请确保你的系统安装了 NSimsun 字体，否则可能有字体不能完全对齐
的情况。

# 加 入

我们欢迎各种各样的帮助，翻译，测试，等等等等。如果你也想加入本项目的话，请直接
与我们联系 (见下)，同时请先行阅读 guides.txt。

AUTHORS 列出了翻译人员。

LICENSE 包括版权信息。

# 信 息

欢迎访问我们的主页以获取更多的信息和最新的版本:

https://github.com/yianwillis/vimcdoc

这将是我们的新主页。原版本 http://vimcdoc.sf.net (English) 的内容已经完整导入。
以后的更新也只会在 github 进行。


# 联 系

任何建议、问题等等，请送往 yianwillis@gmail.com。
