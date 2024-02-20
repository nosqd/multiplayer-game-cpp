COMMON_ARGS = -lopengl32
SFML_ARGS = -Ilib/SFML/include -Llib/SFML/lib -lsfml-system -lsfml-graphics -lsfml-main -lsfml-window -lsfml-audio
IMGUI_ARGS = -Ilib/imgui/ lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_impl_win32.cpp lib/imgui/imgui_widgets.cpp lib/imgui/imgui_tables.cpp
IMGUI_SFML_ARGS = -Ilib/imgui-sfml/ lib/imgui-sfml/imgui-SFML.cpp
game: src/main.cpp clean
	cp -r lib/SFML/bin/*.dll dist/
	cp -r res/ dist/
	clang -o dist/game.exe $(COMMON_ARGS) $(SFML_ARGS) $(IMGUI_ARGS) $(IMGUI_SFML_ARGS) src/main.cpp src/player/CPlayer.cpp src/game/CGame.cpp src/input/CInput.cpp src/ball/CBall.cpp

clean:
	rm -rf dist
	mkdir -p dist