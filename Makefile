
LIBS = -LC:\mingw-w64\lib\bullet -LC:\mingw-w64\lib -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lIrrlicht -lm -lpthread -lfreetype dep\OpenAL32.dll
INCLUDEDIRECTORIES = -IC:\mingw-w64\include\bullet -IC:\mingw-w64\include -Iengine\src\css -Iengine\src\lib

CP = copy
RM = del
CXX = g++
CC = gcc

RM_FLAGS = /f
CFLAGS =  -m64 -ggdb -g3 -ggdb3 -g
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

MAINOBJECTS = game\\bin\\Character.o game\\bin\\Event.o game\\bin\\GetVersion.o game\\bin\\MeshLoader.o game\\bin\\ModulesLoader.o game\\bin\\Init.o game\\bin\\Player.o game\\bin\\ShapesLoader.o game\\bin\\SoundsLoader.o

GAMECOREMODULESOBJECTS = 
GAMECOREMODULES = 
RELEASEGAMECOREMODULES = $(subst game,release,$(GAMECOREMODULES))

ENGINECOREOBJECTS = engine\\bin\\Camera.o engine\\bin\\ClassFactoryBase.o engine\\bin\\CollisionObjectManager.o engine\\bin\\CollisionShapeConstructor.o engine\\bin\\CollisionShapeManager.o engine\\bin\\DllImporter.o engine\\bin\\DynamicEntity.o engine\\bin\\Engine.o engine\\bin\\EngineRayTraceData.o engine\\bin\\Entity.o engine\\bin\\EventReceiverIrrlicht.o engine\\bin\\EventResponser.o engine\\bin\\GUI.o engine\\bin\\Model.o engine\\bin\\ModulesFactory.o engine\\bin\\MotionController.o engine\\bin\\MotionControllerTrigger.o engine\\bin\\SceneNode.o engine\\bin\\SoundEngine.o engine\\bin\\StaticEntity.o engine\\bin\\StringToEnter.o engine\\bin\\TimeCounter.o engine\\bin\\Trigger.o engine\\bin\\Wav.o engine\\bin\\World.o engine\\bin\\Window.o

DEPENDENCIES = Irrlicht.dll libBulletCollision.dll libBulletDynamics.dll libgcc_s_seh-1.dll libLinearMath.dll libstdc++-6.dll libwinpthread-1.dll libyse64.dll mfc100.dll mfc100u.dll msvcp100.dll msvcr100.dll msvcr100_clr0400.dll OpenAL32.dll
RELEASEDEPENDENCIES = $(addprefix release\\,$(DEPENDENCIES))



install: release\\game.exe
release: release\\game.exe
game: game\\game.exe game\\game-core.dll game\\engine.dll $(GAMECOREMODULES)
engine: engine\\engine.dll

run: release\\game.exe
	@cd release && game.exe

release\\game.exe: game\\game.exe release\\engine.dll release\\game-core.dll $(RELEASEDEPENDENCIES) $(RELEASEGAMECOREMODULES) release\\modules.list
	@$(CP) game\game.exe release\game.exe
game\\game.exe: game\\engine.dll game\\game-core.dll game\\bin\\Main.o $(GAMECOREMODULES)
	$(CXX) -o $@ $(CXXFLAGS) game\engine.dll game\bin\Main.o $(LIBS)


engine\\engine.dll: $(ENGINECOREOBJECTS)
	$(CXX) -shared -fPIC -o $@ $(CXXFLAGS) $^ $(LIBS)

game\\engine.dll: engine\\engine.dll
	@$(CP) engine\engine.dll game\engine.dll
game\\game-core.dll: engine\\engine.dll $(MAINOBJECTS)
	$(CXX) -o $@ -shared -fPIC $(CXXFLAGS) $^ $(LIBS)

game\\dlls\\Trigger.dll: game\\engine.dll game\\bin\\Trigger.o
	$(CXX) -o $@ -shared -fPIC $(CXXFLAGS) $^ $(LIBS)



release\\modules.list: game\\modules.list
	@$(CP) "$<" "$@"
release\\%.dll: dep\\%.dll
	@$(CP) "$<" "$@"
release\\engine.dll: engine\\engine.dll
	@$(CP) "$<" "$@"
release\\dlls\\%.dll: game\\dlls\\%.dll
	@$(CP) "$<" "$@"
release\\game-core.dll: game\\game-core.dll
	@$(CP) "$<" "$@"



engine\\bin\\%.o: engine\\src\\mtd\\%.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDEDIRECTORIES) $<
game\\bin\\%.o: game\\src\\mtd\\%.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDEDIRECTORIES) $<
engine\\bin\\%.o: engine\\src\\lib\\dll\\%.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDEDIRECTORIES) $<
engine\\bin\\%.o: engine\\src\\lib\\%.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDEDIRECTORIES) $<



.PHONY: clean
clean:
	@$(RM) $(RM_FLAGS) release\game.exe
	@$(RM) $(RM_FLAGS) release\engine.dll
	@$(RM) $(RM_FLAGS) release\game-core.dll
	@$(RM) $(RM_FLAGS) release\modules.list
	@$(RM) $(RM_FLAGS) release\dlls\*.dll
	@$(RM) $(RM_FLAGS) release\*.dll
	
	@$(RM) $(RM_FLAGS) game\bin\*.o
	@$(RM) $(RM_FLAGS) game\game.exe
	@$(RM) $(RM_FLAGS) game\engine.dll
	@$(RM) $(RM_FLAGS) game\game-core.dll
	@$(RM) $(RM_FLAGS) game\dlls\*.dll
	@$(RM) $(RM_FLAGS) game\*.dll
	
	@$(RM) $(RM_FLAGS) engine\bin\*.o
	@$(RM) $(RM_FLAGS) engine\engine.dll
