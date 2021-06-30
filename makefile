

compiler = g++
# dossier avec le code de la lib et on indique qu'on veut du statique
includeFlags = -Iinclude -DSFML_STATIC
# dossier ou trouver le lib à link
getLibDir = -Llib
# libs à link 
linkLibs = -lsfml-audio-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
# on colle tout ça
linkerFlags = $(getLibDir) $(linkLibs)

gameName = GAME
tmpFilePath = $(gameName).tmp
finalFileName = $(gameName).exe 
finalFilePath = bin/$(finalFileName)

# 1) on compile sans link
# 2) on link
# ça marche pas quand je le fais en une fois

game: src/main.cpp
	@echo Compiling ...
	@$(compiler) -c src/main.cpp $(includeFlags) -o $(tmpFilePath)
	@echo Success !
	@echo Linking ...
	@$(compiler) $(tmpFilePath) $(linkerFlags) -o $(finalFilePath)
	@echo Success !
	@del $(tmpFilePath)
	@${finalFilePath}
