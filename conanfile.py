from conans import ConanFile, CMake


class ToolsConan(ConanFile):
    name = "tools"
    version = "0.1.0"
    license = "MIT"
    url = "https://github.com/klusekrules/tools"
    description = "Tools for space explorers project"
    settings = "os", "compiler", "build_type", "arch"
    requires = "parser/0.5@klusek_rules/stable", "luajit/2.0.5@int010h/stable", "Krypto/0.5@klusek_rules/stable"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/tools", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["tools"]
