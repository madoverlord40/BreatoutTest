# BreatoutTest
Programming test for NetVrk

Project took me a total of one work day or about 8hrs.

Planning 1hr
Designing 1hr
Implementation 6hr
Test/Bugfix 2hr

I added quite a bit to this, will be a large download due to textures, materials, music and sounds.
Due to additions in FX, this project took a little bit longer than 3hrs.

Uses C++ for most of the project, blueprints derrived from code.

ABreakoutGameState: Keeps track of the game and score
                    Uses screen fading transitions between levels and title screen.
                    Uses level streeming to unload and load new sub levels.
                    Keeps track of the bricks, on brick destroy increases score, and checks remaining bricks, if 0 NUM transitions to next level.

ABreakoutPlayerController: Handles input, communication with HUD, Communication with GameState

AGamePaddlePawn: Has collider for the ball on the mesh, set to respond to physics hits
                 Is the player pawn during game play.
                 Owns and spawns the ball, called on from player controller.

ABreakoutBall: The ball, setup as physics simulated, locked to XZ plane.

ABrickActor: The bricks in each level, configurable for hit FX and sounds, 3 types, Red,Green,Blue
             Configurable hits required to destroy
             Notifies game state on destroy

AWallActor: Not used, ended up just building in blueprint.

ABreakoutHUD: Holds the widgets for the game, responsible for showing or hiding them according to game state.
