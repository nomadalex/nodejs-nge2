L.add_arg_conv_rule("const char*",
					function (idx)
					   local v = { idx = idx }
					   local str = E("
Local<String> str${idx} = args[${idx}]->ToString();
String::AsciiValue strVal${idx}(str${idx});
const char* rarg${idx} = *strVal${idx};
", v)
					   return str, E("rarg${idx}", v)
					end)

L.add_arg_conv_rule("int",
					function (idx)
					   local v = { idx = idx }
					   local str = E("
Local<Integer> integer${idx} = args[${idx}]->ToInteger();
int rarg${idx} = integer${idx}->Value();
", v)
					   return str, E("rarg${idx}", v)
					end)

L.add_struct({ { "uint32",  "w" },
			   { "uint32",  "h" },
			   { "uint32",  "texw" },
			   { "uint32",  "texh" },
			   { "uint8",   "bpb" },
			   { "uint8",   "swizzle" },
			   { "uint32",  "mode" },
			   { "uint32",  "dtype" },
			   { "uint8*",  "data", jsType = "Buffer" },
			   { "float",   "rcentrex" },
			   { "float",   "rcentrey" },
			   { "uint32",  "texid" },
			   { "uint8",   "modified" },
			   { "uint8",   "dontswizzle" },
			   { "int",     "mask" }
			 })

L.add_function({ "image_p", "image_load", {"const char*", "int", "int"} })
L.add_function({ "image_p", "image_load_buf", { "const char*", "int", "int", "int" } })

