from conan import ConanFile

class MoxPPRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("spdlog/1.12.0")
        self.requires("nlohmann_json/3.11.2")

    def configure(self):
        self.options["spdlog"].wchar_support = True
