
#pragma once

#include <string>
#include <vector>
#include "TinyXML-2/tinyxml2.h"

class NormalGenLayer {
public:
	std::string layerName;					// visual name of the layer -- the name in the dialog is internally managed to avoid conflicts
	std::string sourceFileName;				// source texture file name.  Accepts special wildcards %gamepath% and %bodyslidepath% on load, but stored as full path.
	std::string maskFileName;				// mask texture file name.   Accepts special wildcards %gamepath% and %bodyslidepath% on load, but stored as full path.
	bool isTangentSpace = true;				// tangent or model space normal map? Model space maps are composited by simply copying over top, applying the mask file, while tangent space perturbs the current normals 
	bool useMeshNormalsSource = false;		// use unperturbed mesh normals as the source data.  This allows a layer to "erase" previous layer normals. Ex:  An area of burned flesh needs skin pore detail to be gone, use an erase layer (this flag) and a mask to erase tertiary detail prior to layering the scar detail.

	bool scaleToResolution = true;			// resize source to full resolution of background, this is important for uvs to line up
	int xOffset = 0;						// UV offset to apply to the normals.  This only really works when a mask selects a small area of the mesh and you want to reposition the data, or it's a small file without being scaled.
	int yOffset = 0;

	bool swapRG = false;					// Swap red/green channels in source map 
	bool invertGreen = false;				// Channel inverts   Green is commonly opposite between dx and opengl.
	bool invertBlue = false;
	bool invertRed = false;					

	/* background layer special properties */
	char fillColor[3];	// A solid color to set the background to, if no original file is to be used as the background
	int resolution;							// the resolution for the in memory texture information and, optionally, output data.  


	NormalGenLayer() { 
		fillColor[0] = 126; fillColor[1] = 127; fillColor[2] = 255;
	}
	~NormalGenLayer() {}

	bool IsBackground() {
		return layerName == "Background";
	}

	static void LoadFromXML(tinyxml2::XMLElement* normalGenSource, std::vector<NormalGenLayer>& outLayers);
	static void SaveToXML(tinyxml2::XMLElement* container, const std::vector<NormalGenLayer>& layers);
};
