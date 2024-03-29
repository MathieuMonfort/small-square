{pkgs ? import <nixpkgs> { config = {allowUnfree = true;};  } }:

	pkgs.mkShell {
		nativeBuildInputs = [
			pkgs.cmake
			pkgs.gnumake
			pkgs.gcc
			pkgs.gdb
			
			pkgs.glfw3
			pkgs.assimp
			pkgs.zlib
			pkgs.glm
		];
	}
