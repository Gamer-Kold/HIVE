{
  description = "HIVE dev environment";
  nixConfig.bash-prompt = "[nix(HIVE)] ";
  inputs = 
  { 
  nixpkgs.url = "github:nixos/nixpkgs/23.11"; 
  zig.url = "github:mitchellh/zig-overlay";
  };

  outputs = { self, zig, nixpkgs }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux.pkgs;
    in {
      devShells.x86_64-linux.default = pkgs.mkShell {
        name = "HIVE build environment";
        buildInputs = [
	zig.packages.master
	pkgs.clang
        ];
      };
    };
}
