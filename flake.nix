{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    pkgs = import nixpkgs {system = "x86_64-linux";};

    developEnv = pkgs.clangStdenv;
    boostOverride = pkgs.boost.override {
      stdenv = developEnv;
      enableShared = false;
      enabledStatic = true;
      enableDebug = true;
    };
    # sdl2Override = pkgs.SDL2.override {
    #   stdenv = developEnv;
    #   withStatic = true;
    # };
    imguiOverride = pkgs.imgui.override {
      stdenv = developEnv;
      IMGUI_BUILD_GLFW_BINDING = false;
      IMGUI_BUILD_SDL2_BINDING = false;
      IMGUI_BUILD_VULKAN_BINDING = false;
    };
    # assimpOverride = pkgs.assimp.overrideAttrs (oldAttrs: {
    #   stdenv = developEnv;
    #   cmakeFlags = ["-DASSIMP_BUILD_ASSIMP_TOOLS=ON" "-DBUILD_SHARED_LIBS=OFF"];
    # });
  in {
    devShells.x86_64-linux.default = pkgs.mkShell.override {stdenv = developEnv;} {
      name = "developEnv";
      packages = with pkgs; [
        # libGL
        # xorg.libX11
        # xorg.libXi
        # xorg.libXcursor
        # xorg.libXrandr
        # xorg.libXScrnSaver

        boostOverride
        imguiOverride
        SDL2
        assimp

        gdb
        cmake
        ninja
      ];
      hardeningDisable = ["all"];
    };
  };
}
