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
  in {
    devShells.x86_64-linux.default = pkgs.mkShell.override {stdenv = developEnv;} {
      name = "developEnv";
      packages = with pkgs; [
        boostOverride
        gdb
        cmake
        ninja
      ];
      hardeningDisable = ["all"];
    };
  };
}
