import glob
import os
import shutil

from SCons.Script import *

# variables from this list are replaced
REPLACE_VARS = set(['CXX', 'CC'])

def loadSourceFiles(env, srcDir, mode, target):

	print("  Finding source files in {0}".format(srcDir))

	list = []

	for root, dirnames, filenames in os.walk(srcDir):

		print("    adding dir {0}".format(root))

		path = "build/" + mode + "/" + target + "/" + root
		
		env.VariantDir(path, root, duplicate=0)

		list = list + Glob(path + "/*.cpp")

	return list

def loadEnvVars(env, filepath):

	with open(filepath, 'r') as f:
 		for line in f:

			# ignore whitepace or comment lines
			if line.isspace() or line[0] == "#":
				continue

			# each line should be VAR=VAL
 			values = line.split("=", 1)
 						
			values[1] = values[1].rstrip()

			# expand environment variables
			values[1] = os.path.expandvars(values[1])

 			# handle setting scons style parameters: ['param1', 'param2']
 			if values[1][0] == "[":
 				values[1] = eval(values[1])
 				
 				# TODO: if it doesn't start with "[", throw an error
 				
 			if values[0] in env and values[0] not in REPLACE_VARS:
				
 				env[values[0]] += values[1]
 			else:
 				env[values[0]] = values[1]

def initDefaultEnv(mode, target):

	env = DefaultEnvironment()

	loadEnvVars(env, 'vars/modes/' + mode)
	loadEnvVars(env, 'vars/targets/' + target)

	artifactLocation = "build/" + mode + "/" + target + "/"	

	if 'LIBPATH' in env:
		env['LIBPATH'].Append([artifactLocation + "lib/"])
	else:
		env['LIBPATH'] = [artifactLocation + "lib/"]

def initArtifact(name, srcDir, binaryType, sconsFlagsFile, mode, target, flags):	

	print("Preparing artifact {0}".format(name))

	env = DefaultEnvironment().Clone()
	
	loadEnvVars(env, sconsFlagsFile)

	if not flags.isspace():
		env.MergeFlags(env.ParseFlags(flags))

	sourceFiles = loadSourceFiles(env, srcDir, mode, target)
	
	artifactLocation = "build/" + mode + "/" + target + "/"	

	if binaryType == "shared":
		prog = env.SharedLibrary(artifactLocation + "/lib/" + name, sourceFiles)

	elif binaryType == "static":
		prog = env.StaticLibrary(artifactLocation + "/lib/" + name, sourceFiles)

	elif binaryType == "program":
		prog = env.Program(artifactLocation + "/bin/" + name, sourceFiles)

	return prog
	
print "BUILD_TARGETS is", map(str, BUILD_TARGETS)

mode = ARGUMENTS.get('mode', 'debug')
target = ARGUMENTS.get('target', 'linux')
flags = ARGUMENTS.get('flags', '')

initDefaultEnv(mode, target)

initArtifact('test1', 'test1', 'program', 'test1/test1.scons', mode, target, flags)
