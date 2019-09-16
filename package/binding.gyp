{
    "targets": [
        {
            "target_name": "code_audit",
            "sources": ["src/module.cpp", "src/object_wrapper.cpp"],
            'include_dirs': [
              "<!@(node -p \"require('node-addon-api').include\")",
              "../core/include",
              "../distributed/include"
            ],
            "link_settings": {
               "libraries": [
                 "-lcode_audit_core",
                 "-lcode_audit_distributed",
               ],
               "ldflags": [
                   "-L<(module_root_dir)/../core/bin",
                   "-Wl,-rpath,<(module_root_dir)/../core/bin",
                   "-L<(module_root_dir)/../distributed/bin",
                   "-Wl,-rpath,<(module_root_dir)/../distributed/bin",
               ]
             },
            'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
              'CLANG_CXX_LIBRARY': 'libc++',
              'MACOSX_DEPLOYMENT_TARGET': '10.7',
            },
            'msvs_settings': {
              'VCCLCompilerTool': { 'ExceptionHandling': 1 },
            },
        }
    ],
}