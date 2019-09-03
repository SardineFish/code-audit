{
    "targets": [
        {
            "target_name": "code_audit",
            "sources": ["src/module.cpp"],
            'include_dirs': [
              "<!@(node -p \"require('node-addon-api').include\")",
              "../core/include"
            ],
            'libraries': [
              "<(module_root_dir)/../core/bin/libcode_audit_core.a"
            ],
            'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
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