#!/usr/bin/env python3

from distutils.core import setup, Extension

xdotoolc = Extension('_xdotool',
                        include_dirs=['xdotoolsrc',
                        '/usr/include/',
                        '/usr/include/X11',
                        '/usr/include/X11/extensions',
                        '/usr/include/xkbccommon'],
                        sources=['xdotoolsrc/tool.c',
                                'xdotoolsrc/xdo.c',
                                'xdotoolsrc/xdotool.c',
                                'xdotoolsrc/cmd_key.c',
                                'xdotoolsrc/cmd_click.c',
                                'xdotoolsrc/cmd_mousemove.c',
                                'xdotoolsrc/cmd_mousemove_relative.c'
                                ],
                        extra_compile_args=[
                                '-Wall',
                                '-O0',
                                '-g'
                        ],
                        extra_link_args=[
                                '-L.',
                                 #'-lxdo',
                                '-Xlinker',
                                '-rpath',
                                '/usr/local/lib',
                                '-lm',
                                '-lX11',
                                '-lrt',
                                '-lXtst',
                                '-lXinerama',
                                '-lxkbcommon'
                        ]
                )

setup(name='xdotool_py', version='0.01', \
        ext_modules=[xdotoolc],
        packages=['xdotool_py'],
        package_dir={'xdotool_py': 'xdotool_py'})
