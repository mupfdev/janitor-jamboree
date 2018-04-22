{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
    name = "janitor-jamboree-git";

    src = pkgs.fetchFromGitHub {
        owner = "mupfelofen-de";
        repo = "janitor-jamboree";
        rev = "163ec454192fe38e29195a58b0a4b8fc0211774e";
        sha256 = "0dgnwqc5sizkxlgf1inrfmd10jnlv55nym3sdg5ifgbai04wipi7";
    };

    buildInputs = with pkgs; [
        libxml2
        SDL2
        SDL2_image
        SDL2_mixer
        zlib
    ];

    installPhase = ''
        install -Dsm 755 janitor-jamboree $out/bin/janitor-jamboree
    '';
}
