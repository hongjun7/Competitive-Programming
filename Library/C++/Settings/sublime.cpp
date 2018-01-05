1. Preferences - Settings
{
	"color_scheme": "Packages/Color Scheme - Default/Monokai.tmTheme",
	"font_face": "Ubuntu Mono Regular",
	"font_size": 15,
	"ignored_packages": ["Vintage"],
	"theme": "Default.sublime-theme"
}
2. Preferences - Key Bindings
[
	{ "keys": ["ctrl+shift+i"], "command": "reindent" , "args": { "single_line": false } }
]
3. Tools - Build System - New Build System
{
	"shell_cmd": "g++ \"${file}\" -o \"${file_path}/${file_base_name}\"",
	"file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
	"working_dir": "${file_path}",
	"selector": "source.c, source.c++",
	"variants":
	[
		{
			"name": "Run",
			"shell_cmd": "g++ -std=c++11 \"${file}\" -o \"${file_path}/${file_base_name}\" && \"${file_path}/${file_base_name}\" < input.txt"
		}
	]
}