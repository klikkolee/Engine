#include "choreographer.h"
#include "window.h"
#include "mesh.h"
#include "matrix4.h"
#include "quaternion.h"
#include "log.h"
#include "input.h"
#include "camera.h"
#include "game_object.h"
#include "component.h"
#include "SDL.h"
#include "GL\glew.h"
#include <memory>
#include <unordered_map>
#include <assert.h>
#include <string>
#include <fstream>

namespace Choreographer
{
	bool isInitialized = false;
	bool isRunning = false;
	bool stopOnMainWindowClose = true;
	std::unique_ptr<Window> mainWindow{};
	std::unordered_map<int, std::unique_ptr<Window>> windowMap;
	namespace
	{
		void Initialize();
		GLuint GetShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile); //temp
		void MainLoop()
		{
			//temp
			Mesh mesh = Mesh::TestTriangle();
			Mesh cube = Mesh::TestCube();
			GLuint shaderProgram = GetShaderProgram("red_shader.vp", "red_shader.fp");
			GLuint greenShaderProgram = GetShaderProgram("red_shader.vp", "green_shader.fp");
			GLuint cubeShaderProgram = GetShaderProgram("red_shader.vp", "cube_shader.fp");
			glUseProgram(shaderProgram);
			glClearColor(0, 0, 0, 1);


			Matrix4 modelMatrix = Matrix4::TranslationMatrix(0, 0, 10);// = Matrix4::ProjectionMatrix(45, .1, 1000, 800 / 600) *Matrix4::TranslationMatrix(0, 0, 10);
			Matrix4 cubeModelMatrix = Matrix4::TranslationMatrix(10, 0, 10);
			Matrix4 viewMatrix = Matrix4::TranslationMatrix(0, 0, 10);
			Matrix4 ProjectionMatrix = Matrix4::ProjectionMatrix(90, .1, 1000, 800.0f / 600.0f);
			Matrix4 mvp;

			GLuint mvpUniform = glGetUniformLocation(shaderProgram, "MVP");

			Uint32 startFrameTime = SDL_GetTicks();
			Uint32 endFrameTime = startFrameTime;
			Uint32 delta = 0;
			
			GameObject mainCameraObject{};
			mainCameraObject.AddComponent<Camera>();

			//endtemp
			while (isRunning)
			{
				startFrameTime = SDL_GetTicks();
				SDL_Event event;
				Uint32 startPollTime = SDL_GetTicks();
				Uint32 endPollTime = SDL_GetTicks();
				while(SDL_WaitEventTimeout(&event, 5))
				{
					switch (event.type)
					{
					case SDL_WINDOWEVENT:
						if (event.window.event == SDL_WINDOWEVENT_CLOSE)
						{
							if (event.window.windowID == mainWindow->GetID() &&
								stopOnMainWindowClose)
							{
								Stop();
							}
							windowMap.erase(event.window.windowID);
						}
						break;
					case SDL_QUIT:
						Stop();
						break;
					}
					//TODO: dispatch events to relevant structures once they exist
					Input::ProcessEvent(event);
					endPollTime = SDL_GetTicks();
				}
				//temp
				mainWindow->BindAsRenderTarget();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				float mvpFloatBuffer[16] = {};
				if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_UP))
				{
					mainCameraObject.transform.Rotate(-1.0f*delta / 1000,0,0);
				}
				else if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_DOWN))
				{
					mainCameraObject.transform.Rotate(1.0f*delta / 1000,0,0);
				}
				if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_RIGHT))
				{
					mainCameraObject.transform.Rotate(0,1.0f*delta / 1000,0);
				}
				else if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_LEFT))
				{
					mainCameraObject.transform.Rotate(0, 1.0f*delta / 1000,0);
				}
				if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_w))
				{
					mainCameraObject.transform.Translate(mainCameraObject.transform.Forward()*5.0f*delta / 1000);
				}
				else if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_s))
				{
					mainCameraObject.transform.Translate(-mainCameraObject.transform.Forward()*5.0f*delta / 1000);
				}
				if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_a))
				{
					mainCameraObject.transform.Translate(-mainCameraObject.transform.Right()*5.0f*delta / 1000);
				}
				else if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_d))
				{
					mainCameraObject.transform.Translate(mainCameraObject.transform.Right()*5.0f*delta / 1000);
				}
				if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_LSHIFT))
				{
					mainCameraObject.transform.Translate(-mainCameraObject.transform.Up()*5.0f*delta / 1000);
				}
				else if (Input::IsKeyPressed(mainWindow->GetID(), SDLK_SPACE))
				{
					mainCameraObject.transform.Translate(mainCameraObject.transform.Up()*5.0f*delta / 1000);
				}
				viewMatrix = mainCameraObject.transform.LocalToWorldMatrix();//Matrix4::EulerRotationRadian(-mainCamera.xRot, -mainCamera.yRot, 0) * Matrix4::TranslationMatrix(-mainCamera.translation);
				glUseProgram(shaderProgram);
				mvp = ProjectionMatrix*viewMatrix*modelMatrix;
				mvp.AsFloatBuffer(mvpFloatBuffer);
				glUniformMatrix4fv(mvpUniform, 1, GL_TRUE, mvpFloatBuffer);
				mesh.Draw();
				glUseProgram(greenShaderProgram);
				mvp = ProjectionMatrix*viewMatrix*modelMatrix*Matrix4::EulerRotationDegree(0, 180, 0);
				mvp.AsFloatBuffer(mvpFloatBuffer);
				glUniformMatrix4fv(mvpUniform, 1, GL_TRUE, mvpFloatBuffer);
				mesh.Draw();

				glUseProgram(cubeShaderProgram);
				mvp = ProjectionMatrix*viewMatrix*cubeModelMatrix;
				mvp.AsFloatBuffer(mvpFloatBuffer);
				glUniformMatrix4fv(mvpUniform, 1, GL_TRUE, mvpFloatBuffer);
				cube.Draw();
				glUseProgram(greenShaderProgram);
				glUniformMatrix4fv(mvpUniform, 1, GL_TRUE, mvpFloatBuffer);
				glCullFace(GL_FRONT);
				cube.Draw();
				glCullFace(GL_BACK);

				mainWindow->SwapBuffers();
				//endtemp
				endFrameTime = SDL_GetTicks();
				if (endFrameTime - startFrameTime<16)
					SDL_Delay(16 - (endFrameTime - startFrameTime));
				endFrameTime = SDL_GetTicks();
				delta = endFrameTime - startFrameTime;
			}
		}
		void Initialize()
		{
			if (isInitialized) return;
			glewExperimental = GL_TRUE;;
			SDL_Init(SDL_INIT_EVERYTHING);
			SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, 0);
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			mainWindow = std::make_unique<Window>(800, 600, "Title");

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);

			SDL_GL_SetSwapInterval(1);

			GLenum glewError = glewInit();
			if (glewError != GLEW_OK)
			{
				fprintf(LogFile(), "Error: '%s'\n", glewGetErrorString(glewError));
				assert(0);
			}

			isInitialized = true;
		}
		GLuint GetShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
		{
			GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexShaderCode;
			std::ifstream vertexShaderStream(vertexShaderFile, std::ios::in);
			if (vertexShaderStream.is_open()) {
				std::string Line = "";
				while (getline(vertexShaderStream, Line))
					vertexShaderCode += "\n" + Line;
				vertexShaderStream.close();
			}
			else {
				fprintf(LogFile(), "unable to open shader from file %s", vertexShaderFile.c_str());
				assert(0);
				return GL_FALSE;
			}

			std::string fragmentShaderCode;
			std::ifstream fragmentShaderStream(fragmentShaderFile, std::ios::in);
			if (fragmentShaderStream.is_open()) {
				std::string Line = "";
				while (getline(fragmentShaderStream, Line))
					fragmentShaderCode += "\n" + Line;
				fragmentShaderStream.close();
			}
			else {
				fprintf(LogFile(), "unable to open shader from file %s", fragmentShaderFile.c_str());
				assert(0);
				return GL_FALSE;
			}

			GLint result = GL_FALSE;
			int infoLogLength;

			const char* vertexShaderCodeCString = vertexShaderCode.c_str();
			const char*fragmentShaderCodeCString = fragmentShaderCode.c_str();

			glShaderSource(vertexShaderID, 1, &vertexShaderCodeCString, nullptr);

			glCompileShader(vertexShaderID);

			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<char> verrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &verrorMessage[0]);
			assert(result);

			glShaderSource(fragmentShaderID, 1, &fragmentShaderCodeCString, nullptr);

			glCompileShader(fragmentShaderID);

			glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<char> ferrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &ferrorMessage[0]);
			assert(result);

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<char> perrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &perrorMessage[0]);
			assert(result);

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return programID;
		}
	}

	void Choreographer::Start()
	{
		if (!isInitialized)
		{
			Initialize();
		}
		if (!isRunning)
		{
			isRunning = true;
			MainLoop();
		}
	}
	}
	

void Choreographer::Stop()
{
	isRunning = false;
}

void Choreographer::SetStopOnMainWindowClose(bool value)
{
	stopOnMainWindowClose = value;
}

//temp

//endtemp