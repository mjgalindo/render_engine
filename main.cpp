/* ---------------------------------------------------------------------------
** main.cpp
** Main file that runs the ray tracer. The defined scenes in the displayed menu can
** be rendered, and configured with various parameters in relation to the algorithm.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <iostream>
#include <pinhole.hpp>
#include <scene.hpp>
#include <sceneSamples.hpp>
#include <thread>
#include <sstream>
#include <map>

using namespace std;

/**
 * Filled in runtime. Contains all available scene names and pointers to the functions
 * that return their corresponding scenes
 */
map<string, function<Scene(void)>> SCENE_NAMES;

/**
 * Splits a string by the delimiter returning a vector of strings.
 * @param input input string to split by delim.
 * @param delim char by which s will be split.
 * @return vector of all the split strings in s.
 */
vector<string> split(const string &input, char delim) {
    vector<string> retVal;
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delim)) {
        retVal.push_back(item);
    }
    return retVal;
}

/**
 * Prints some information about the usage of this program. Takes scene names from SCENE_NAMES which must
 * be filled before calling this function.
 */
void PrintHelp()
{
    cout << "Usage: [OPTION]*\n"
            "If no options are specified, a default Cornell box with 64 indirect rays will be rendered and saved as cornell.ppm.\n"
            "\n"
            "Some images will not look good by default, in such cases use --gamma, to use a gamma correction of 2.2, or --clamp to limit color values to the maximum.\n\n"
            "Available options:\n"
            "\t-h : Print this helpful text.\n"
            "\t-res <WIDTHxHEIGHT> : Select a different resolution for the result image.\n"
            "\t--indirect_steps <NUMBER>: Choose the number of indirect lighting steps to render images faster. 0 to disable indirect lighting.\n"
            "\t--indirect_rays <NUMBER> : Sets the number of indirect rays that will be used to render the image.\n"
            "\t--clamp : Instead of dividing by the greatest color value in the image, all colors will be clamped.\n"
            "\t--gamma : Instead of dividing by the greatest color value in the image, all colors will be gamma corrected and then clamped.\n"
            "\t-s [SCENE_NAME] : Selects the scene to render.\n"
            "\n"
            "Available scenes:\n";
    for (const auto &scenePair: SCENE_NAMES)
        cout << '\t' << scenePair.first << '\n';
}

/**
 *  Initializes the map of names and functions SCENE_NAMES .
 */
void InitializeSceneNames()
{
    SCENE_NAMES["chess_texture"] = &ChessTexture;
    SCENE_NAMES["cornell"] = &CornellBox;
    SCENE_NAMES["diamond_sphere"] = &RefractiveSphereTest<3>;
    SCENE_NAMES["dragon"] = &Dragon;
    SCENE_NAMES["experimental"] = &Experimental;
    SCENE_NAMES["glass_sphere"] = &RefractiveSphereTest<1>;
    SCENE_NAMES["glass_sphere_2"] = &RefractionPlaneSphere;
    SCENE_NAMES["indirect"] = &IndirectLighting;
    SCENE_NAMES["infinite_mirror"] = &FacingMirrors;
    SCENE_NAMES["menger_1"] = &Menger<1>;
    SCENE_NAMES["menger_2"] = &Menger<2>;
    SCENE_NAMES["menger_3"] = &Menger<3>;
    SCENE_NAMES["menger_4"] = &Menger<4>;
    SCENE_NAMES["menger_5"] = &Menger<5>;
    SCENE_NAMES["phong_spheres"] = &PhongSphereSamples;
    SCENE_NAMES["quartz_sphere"] = &RefractiveSphereTest<4>;
    SCENE_NAMES["room"] = &Room;
    SCENE_NAMES["specular_lobe_1"] = &SpecularLobes<3>;
    SCENE_NAMES["specular_lobe_2"] = &SpecularLobes<10>;
    SCENE_NAMES["specular_lobe_3"] = &SpecularLobes<100>;
    SCENE_NAMES["spheres"] = &ManySpheres;
    SCENE_NAMES["teapot"] = &Teapot;
    SCENE_NAMES["water_sphere"] = &RefractiveSphereTest<2>;
}

/**
 * Main function. Renders a handful of hardcoded scenes as a way to test what the ray tracer can do.
 * @return 0 if everything worked fine, 1 otherwise.
 */
int main(int argc, char * argv[])
{
    InitializeSceneNames();
    int width = -1, height = -1;
    unsigned int indirectSteps = 1, indirectRays = 64;
    unsigned int threadCount = thread::hardware_concurrency(); // Use all available threads by default.
    SaveMode saveMode = DIM_TO_WHITE;
    string sceneName = "cornell";

    // Put the arguments in a string vector to make them more accessible.
    vector<string> arguments(argv + 1, argv + argc);
    unsigned long argnum = arguments.size();
    /** Parse all options modifying the necessary variables and returning 1 on error */
    for (unsigned int i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "-h")
        {
            PrintHelp();
            return 0;
        }

        else if (arguments[i] == "-res")
        {
            if (i + 1 >= argnum)
            {
                cerr << "You need to specify resolution as WIDTHxHEIGHT\n"; return 1;
            }
            auto widthHeight = split(arguments[i+1], 'x');
            // Knowingly not bothering to check if the arguments are ints.
            width = stoi(widthHeight[0]);
            height = stoi(widthHeight[1]);
            ++i;
        }

        else if (arguments[i] == "--indirect_steps")
        {
            indirectSteps = (unsigned int) stoi(arguments[i+1]);
            i++;
        }

        else if (arguments[i] == "--indirect_rays")
        {
            indirectRays = (unsigned int) stoi(arguments[i+1]);
            i++;
        }

        else if (arguments[i] == "-j")
        {
            try
            {
                if (i + 1 < argnum)
                {
                    int tmp = stoi(arguments[i+1]);
                    threadCount = (unsigned int) tmp;
                    i++;
                }
            }catch(invalid_argument){/*Do nothing*/}
        }

        else if (arguments[i] == "--gamma")
        {
            saveMode = GAMMA;
        }

        else if (arguments[i] == "--clamp")
        {
            saveMode = CLAMP;
        }

        else if (arguments[i] == "-s")
        {
            if (i + 1 < argnum)
            {
                sceneName = arguments[i+1];
            }
            else
            {
                cerr << "You need to specify a scene. Use the option '-h' to see all available scenes.\n";
                return 1;
            }
            i++;
        }
        else
        {
            cerr << "Unrecognized argument '" << arguments[i] << "' use '-h' to see all available arguments\n";
            return 1;
        }
    }

    if (argnum == 0)
    {
        cout << "Rendering the default Cornell Box. Use the option '-h' if you want to see all available scenes.\n";
    }

    Scene chosenScene;
    // Calls the chosen scene function from the scene name map.
    if (SCENE_NAMES.find(sceneName) != SCENE_NAMES.end())
    {
        chosenScene = SCENE_NAMES[sceneName]();
    }
    else
    {
        cerr << "The scene " << sceneName << " is invalid.\n";
        return 1;
    }

    if (width != -1 and height != -1)
    {
        chosenScene.SetImageDimensions((unsigned int)width, (unsigned int)height);
    }

    // Set indirect values for rendering the scene
    chosenScene.SetIndirectSteps(indirectSteps);
    chosenScene.SetIndirectRays(indirectRays);

    // Render the scene and save the resulting image
    auto image = chosenScene.RenderMultiThread(threadCount);
    image->Save(sceneName + ".ppm", saveMode);

    cout << "\nSaved image " << sceneName << ".ppm\n";
    return 0;
}