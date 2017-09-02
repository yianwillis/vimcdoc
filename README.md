macvimcdoc
=======

MacVim 中文文档

# 关 于

这是 MacVim 版本的中文文档，基于 vimcdoc 的中文文档，并加上 MacVim 相关的文档的
中文翻译。 关于 vimcdoc，详见 https://github.com/yianwillis/vimcdoc。

# 安装

## Vim 8.0 自带软件包支持

```shell
$ mkdir -p ~/.vim/pack/foo/start
$ cd ~/.vim/pack/foo/start
$ git clone git://github.com/yianwillis/macvimcdoc.git
```

重启 Vim。

其中 foo 可以是任何你自选的名字。

## Vundle

.vimrc 中加入：

```
Plugin "yianwillis/macvimcdoc"
```

重启 Vim 后执行 `:PluginInstall`。

## NeoBundle

.vimrc 中加入：

```
NeoBundle 'yianwillis/macvimcdoc"
```

重启 Vim 后执行命令 `:NeoBundleInstall`。

## Pathogen

```shell
$ cd ~/.vim/bundle
$ git clone git://github.com/yianwillis/macvimcdoc.git
```

重启 Vim。

## vim-plug

.vimrc 中加入:

```
Plug 'yianwillis/macvimcdoc'
```

重启 Vim 后执行命令 `:PlugInstall`。

# 信 息

欢迎访问我们的主页以获取更多的信息和最新的版本:

https://github.com/yianwillis/macvimcdoc

# 联 系

任何建议、问题等等，请送往 yianwillis@gmail.com。
