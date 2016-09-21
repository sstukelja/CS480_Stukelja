#include <iostream>
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  cout << "Menu:" << endl;
  cout << "Press R to start/stop the rotation" << endl;
  cout << "Press O to start/stop the orbit" << endl;
  cout << "Press P to pause the object" << endl;
  cout << "Click with either mouse button to reverse direction" << endl;
  cout << "Press M to print this menu again" << endl;

  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT, direction, pause);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
	if (m_event.key.keysym.sym == SDLK_r)
	{
        if(pause == 1)
            pause = 0;
        else
            pause = 1;
	}
    if (m_event.key.keysym.sym == SDLK_o)
	{
        if(pause == 2)
        {
            pause = 0;
            m_DT = pause_DT;
        }
        else
        {
            pause = 2;
            pause_DT = m_DT;
        }
	}
    if (m_event.key.keysym.sym == SDLK_p)
	{
        if(pause == 3)
            pause = 0;
        else
            pause = 3;
	}
    if (m_event.key.keysym.sym == SDLK_m)
	{
		cout << "Menu:" << endl;
        cout << "Press R to start/stop the rotation" << endl;
        cout << "Press O to start/stop the orbit" << endl;
        cout << "Press P to pause the object" << endl;
        cout << "Click with either mouse button to reverse direction" << endl;
        cout << "Press M to print this menu again" << endl;
	}
  }
  if (m_event.button.type == SDL_MOUSEBUTTONDOWN)
  {
    if(direction)
        direction = false;
    else
        direction = true;
  }
  if (m_event.key.keysym.sym == SDLK_LEFT)
	{
        direction = false;
	}
  if (m_event.key.keysym.sym == SDLK_RIGHT)
	{
        direction = true;
	}
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
