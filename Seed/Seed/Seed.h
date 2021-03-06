#pragma once

#include "Resource.h"



void	SetActiveWindowPane(int id, HINSTANCE hInstance, DLGPROC callback);

INT_PTR CALLBACK    BroadLeafCallback(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PineCallback(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PalmCallback(HWND, UINT, WPARAM, LPARAM);