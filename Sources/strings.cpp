#include "strings.h"

namespace SkyStrings {
    char* appName() { return "Sky Renderer:"; }
    char* rayleighLabel() { return "Rayleigh scattering:"; }
    char* rayleighTooltip() { return"Elastic scattering of light by particles smaller than the wavelength of the light. Rayleigh scattering causes the blue hue of the daytime sky and the reddening of the sun at sunset."; }
    char* mieLabel() { return "Mie scattering:"; }
    char* mieTooltip() { return "Elastic scattering of light by particles bigger than the wavelength of the light. The grey/white colour of the clouds is caused by Mie scattering by water droplets which are of a comparable size to the wavelengths of visible light."; }
    char* angleLabel() { return "Angle:"; }
    char* renderButtonText() { return "Render"; }
    char* selectValues() { return "Select parameter values"; }
    char* rendering() { return "Rendering..."; }
    char* whereToSave() { return "Choose where to save the rendered image"; }
    char* defaultFileName() { return "rendered_sky.jpg"; }
    char* filenameFilter() { return "JPG (*.jpg)"; }
    char* blueTextColor() { return "QLabel { color : blue; }"; }
    char* greenTextColor() { return "QLabel { color : green; }"; }
    char* filenameWarning() { return "You must choose a filename before rendering the image."; }
    char* finishedIn() { return "Finished in "; }
    char* seconds() { return " seconds"; }
    char* appInfo() { return "App Info"; }
    char* info() { return"Sky Renderer, version 1.0\n\nThis app is for educational purposes only. It is made for a class at VSITE college.\n\nThe algorithm for rendering the sky is not mine, but this C++ implementation along with the UI makes for a good demonstration app.\n\nDinko Mihovilović\n\nMore about scattering:\n\nMore on scattering:\n\nThe change of sky colour at sunset (red nearest the sun, blue furthest away) is caused by Rayleigh scattering by atmospheric gas particles which are much smaller than the wavelengths of visible light. The grey/white colour of the clouds is caused by Mie scattering by water droplets which are of a comparable size to the wavelengths of visible light."; }
}
