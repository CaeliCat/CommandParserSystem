add_rules("mode.debug", "mode.release")

target("CommandParserSystem")
    set_kind("binary")
    add_files("src/*.cpp")
    set_languages("cxx20")