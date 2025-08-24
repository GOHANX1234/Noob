#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <KittyMemory/KittyMemory.h>
#include <KittyMemory/MemoryPatch.h>
#include <KittyMemory/KittyScanner.h>
#include <KittyMemory/KittyUtils.h>
#include "oxorany/oxorany.h"
#include <xdl.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "DevelopEyeHook/gui.hpp"
//#include "fonts/FontAwesome6_solid.h"
#include "DevelopEye.hpp"
#include "imgui/Font.h"
#include "DevelopEyeMods/Icon.h"
#include "DevelopEyeMods/CN.h"
//#include "DevelopEyeMods/Iconcpp.h"
//#include "DevelopEyeMods/ImguiPP.cpp"
//#include "Chams.h"
#include <Themes.h>
#include "Firewall.h"
#include "exptime.h"
#include "DevelopEye.h"
#include <fstream>
#include "DevelopEyeMods/Base64.h"
#include "DevelopEyeBypass/NawarFirewall1.h"
#include <ctime>
#include "DevelopEyeMods/autofont.h"
//#include "FireWall.h"
#define ICON_MIN_FA 0xf000
#define ICON_MAX_FA 0xf957
#define ICON_FA_GAMEPAD      "\xef\x84\x9b" // U+f11b
#define ICON_FA_GAVEL        "\xef\x83\xa3" // U+f0e3
#define ICON_FA_BAN          "\xef\x81\x9e" // U+f05e
#define ICON_FA_SPINNER      "\xef\x84\x90" // U+f110
#define ICON_FA_HEARTBEAT    "\xef\x88\x9e" // U+f21e
#define ICON_FA_TASKS        "\xef\x82\xae" // U+f0ae
// ======================================================================== //
#define OBFUSCATE(str) str
static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
static float isRedV2 = 0.0f, isGreenV2 = 0.01f, isBlueV2 = 0.0f;
// At the top of your .cpp (ONLY ONCE)
static float pulse = 0.0f;
namespace DevelopEyeMods
{
    bool Toggle(const char* label, bool* v)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        float height = ImGui::GetFrameHeight();
        const ImVec2 pos = window->DC.CursorPos;

        float width = height * 2.0f;
        float radius = height * 0.50f;

        ImVec2 end_pos = ImVec2(
            pos.x + width + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f),
            pos.y + label_size.y + style.FramePadding.y * 2.0f
        );
        const ImRect total_bb(pos, end_pos);

        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        float last_active_id_timer = g.LastActiveIdTimer;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
            g.LastActiveIdTimer = 0.f;
        }

        if (g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed)
            g.LastActiveIdTimer = last_active_id_timer;

        float t = *v ? 1.0f : 0.0f;

        if (g.LastActiveId == id)
        {
            float t_anim = ImSaturate(g.LastActiveIdTimer / 0.16f);
            t = *v ? t_anim : (1.0f - t_anim);
        }

        ImU32 col_bg = ImGui::GetColorU32(
            (held && hovered) ? ImGuiCol_FrameBgActive :
            hovered ? ImGuiCol_FrameBgHovered :
                      ImGuiCol_FrameBg
        );

        ImVec2 frame_end = ImVec2(pos.x + width, pos.y + height);
        const ImRect frame_bb(pos, frame_end);

        ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, col_bg, true, height * 0.5f);
        ImGui::RenderNavHighlight(total_bb, id);

        ImVec2 label_pos = ImVec2(
            frame_bb.Max.x + style.ItemInnerSpacing.x,
            frame_bb.Min.y + style.FramePadding.y
        );
        ImGui::RenderText(label_pos, label);

        float circle_x = pos.x + radius + t * (width - radius * 2.0f);
        float circle_y = pos.y + radius;
        window->DrawList->AddCircleFilled(
            ImVec2(circle_x, circle_y),
            radius - 1.5f,
            ImGui::GetColorU32(ImGuiCol_CheckMark),
            36
        );
        return pressed;
    }
}
bool Items_Esp_Menu = false;
bool FPS = true;
bool HIDEESP = true;
///bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
namespace Settings
{
    static int Tab = 1;
	ImGuiIO& io = ImGui::GetIO();
}
///float density = -1;
// ======================================================================== //
struct My_Patches {
    MemoryPatch Bypass1;
    MemoryPatch Bypass2;
    MemoryPatch Bypass3;
    MemoryPatch Bypass4;
    MemoryPatch Bypass5;
    MemoryPatch Bypass6;
    MemoryPatch Bypass7;
    MemoryPatch Bypass8;
    MemoryPatch Bypass9;
    MemoryPatch Bypass10;
    MemoryPatch Bypass11;
    MemoryPatch Bypass12;
    MemoryPatch Bypass13;
    MemoryPatch Bypass14;
    MemoryPatch Bypass15;
    
    //MemoryPatch NightM;
    MemoryPatch Guest;
} hexPatches;
using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;

void hack();
void writeLog(const std::string& logMessage, const std::string& filename = "/storage/emulated/0/Android/data/com.dualspace.multispace.androidx/files/log.txt");

JavaVM *jvm;
JNIEnv *genv;

class MyModule : public zygisk::ModuleBase {
 public:
  void onLoad(Api *api, JNIEnv *env) override {
    this->api_ = api;
    this->env_ = env;
    genv = env;
   // gEnv = env;

  }

  void preAppSpecialize(AppSpecializeArgs *args) override {
    static constexpr const char *packages[] = {
        "com.dts.freefireth"
    };
    const char *process = env_->GetStringUTFChars(args->nice_name, nullptr);
    for (const auto *package: packages) {
      is_game_ = (strcmp(process, package) == 0);
      if (is_game_) {
        break;
      }
    }
    env_->ReleaseStringUTFChars(args->nice_name, process);
  }

  void postAppSpecialize(const AppSpecializeArgs *args) override {
    if (is_game_) {
       genv->GetJavaVM(&jvm);
     //  genv->GetJavaVM(&gJvm);
      std::thread{hack}.detach();
    }
  }

 private:
  Api *api_ = nullptr;
  JNIEnv *env_ = nullptr;
  bool is_game_ = false;
};


uintptr_t il2cpp_base = 0;
void *getRealAddr(ulong offset) {
return reinterpret_cast<void*>(il2cpp_base + offset);
};


// void (*OpenURL)(String *url); //Expire DevelopEye

static int Tab = 1;
// Expire
/* std::string GetCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%H:%M:%S");
    return oss.str();
}

void OpenURL(Il2CppString* url) {
    typedef void (*OpenURL_t)(Il2CppString*);
    static OpenURL_t openURL = nullptr;
    if (!openURL) {
        openURL = (OpenURL_t)IL2Cpp::Il2CppGetMethodOffset(
            OBFUSCATE("UnityEngine.CoreModule.dll"),
            OBFUSCATE("UnityEngine"),
            OBFUSCATE("Application"),
            OBFUSCATE("OpenURL"),
            1
        );
    }
    if (openURL) {
        openURL(url);
    }
}

void *run_thread(void *arguments)
{
    switch ((int)arguments)
    {
        int dValue;
        float fValue;
    }
    return 0;
} */

void SecureText(const char* encodedBase64) {
    std::string decoded = base64_decode(encodedBase64);
    ImGui::TextUnformatted(decoded.c_str());
}

void SecureTextColored(ImVec4 color, const char* encodedBase64) {
    std::string decoded = base64_decode(encodedBase64);
    ImGui::TextColored(color, decoded.c_str());
}


void ImGui_v_Menu(int s_switch, const char *s_string, bool *b_boolean) {
    ImGui::Checkbox(s_string, b_boolean);
    bool b_setonoff = *b_boolean;
    switch (s_switch) {
    
      case 1:
    if (b_setonoff) {
        hexPatches.Guest.Modify();
    } else {
        hexPatches.Guest.Restore();
    }
    break;
      case 2:
      BypassA = *b_boolean;
    if (BypassA) {
        hexPatches.Bypass1.Modify();
        hexPatches.Bypass2.Modify();
        hexPatches.Bypass3.Modify();
        hexPatches.Bypass4.Modify();
        hexPatches.Bypass5.Modify();
    } else {
        hexPatches.Bypass1.Restore();
        hexPatches.Bypass2.Restore();
        hexPatches.Bypass3.Restore();
        hexPatches.Bypass4.Restore();
        hexPatches.Bypass5.Restore();
    }
    break;
	  case 3:
      BypassB = *b_boolean;
    if (BypassB) {
        hexPatches.Bypass6.Modify();
        hexPatches.Bypass7.Modify();
        hexPatches.Bypass8.Modify();
        hexPatches.Bypass9.Modify();
        hexPatches.Bypass10.Modify();
    } else {
        hexPatches.Bypass6.Restore();
        hexPatches.Bypass7.Restore();
        hexPatches.Bypass8.Restore();
        hexPatches.Bypass9.Restore();
        hexPatches.Bypass10.Restore();
    }
    break;
	  case 4:
      BypassC = *b_boolean;
    if (BypassC) {
        hexPatches.Bypass11.Modify();
        hexPatches.Bypass12.Modify();
        hexPatches.Bypass13.Modify();
        hexPatches.Bypass14.Modify();
        hexPatches.Bypass15.Modify();
    } else {
        hexPatches.Bypass11.Restore();
        hexPatches.Bypass12.Restore();
        hexPatches.Bypass13.Restore();
        hexPatches.Bypass14.Restore();
        hexPatches.Bypass15.Restore();
    }
    break;
      /* case 5:
    if (b_setonoff) {
        hexPatches.NightM.Modify();
    } else {
        hexPatches.NightM.Restore();
    }
    break; */
      default:
      // Handle other cases (if necessary)
    break;
    }
}


bool clearMousePos = true;
bool ImGuiOK = false;
bool initImGui = false;
//bool rainbow = false;
inline EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
inline EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    
eglQuerySurface(dpy, surface, EGL_WIDTH, &g_GlWidth);
eglQuerySurface(dpy, surface, EGL_HEIGHT, &g_GlHeight);

    if (!g_IsSetup) {
        prevWidth = g_GlWidth;
        prevHeight = g_GlHeight;
        SetupImgui();
  
               ImGui_ImplOpenGL3_Init("#version 300 es");

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = NULL;

            
static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0x0900, 0x097F, 0,};
ImFontConfig font_config;
ImFontConfig icons_config;
ImFontConfig CustomFont;
CustomFont.FontDataOwnedByAtlas = false;
icons_config.MergeMode = true;
icons_config.PixelSnapH = true;
icons_config.OversampleH = 2.5;
icons_config.OversampleV = 2.5;
//=====================================| 𝗙𝗢𝗡𝗧𝗦
io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 30.0f, &icons_config, icons_ranges);
io.Fonts->AddFontFromMemoryTTF((void *)Custom_data, Custom_size, 30.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
ImFontConfig cfg;
cfg.SizePixels = ((float) density / 60.0f);
io.Fonts->AddFontDefault(&cfg);
//=====================================| 𝗙𝗢𝗡𝗧𝗦 𝙀𝙉𝘿
g_IsSetup = true;
}
    
    
ImGuiIO &io = ImGui::GetIO();
ImGui::StyleColorsDark();

// Stil referansını al
ImGuiStyle& style = ImGui::GetStyle();

// ✅ Layout Styling (Keep your existing setup)
style.WindowRounding = 10.0f;
style.FrameRounding = 10.0f;
style.FrameBorderSize = 3.0f;
style.WindowBorderSize = 3.0f;
style.ChildBorderSize = 2.5f;
style.TabRounding = 6.0f;

style.ScrollbarSize = 6.0f;
style.ScrollbarRounding = 3.0f;

style.FramePadding = ImVec2(4, 4);
style.ItemSpacing = ImVec2(6, 6);

style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

// ✅ Mix Color Theme with Text
ImVec4* colors = style.Colors;
colors[ImGuiCol_Text]                 = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // White text
colors[ImGuiCol_WindowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.50f); // 50% Transparent bg
colors[ImGuiCol_Border]              = ImVec4(1.0f, 0.00f, 0.00f, 1.00f); // Red border

colors[ImGuiCol_Button]              = ImVec4(0.20f, 0.40f, 0.80f, 1.00f); // Blue button
colors[ImGuiCol_ButtonHovered]       = ImVec4(0.30f, 0.50f, 0.90f, 1.00f);
colors[ImGuiCol_ButtonActive]        = ImVec4(0.15f, 0.35f, 0.70f, 1.00f);

colors[ImGuiCol_FrameBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.50f); // Input bg
//colors[ImGuiCol_FrameBgHovered]      = ImVec4(0.75f, 0.85f, 1.00f, 1.00f);
//colors[ImGuiCol_FrameBgActive]       = ImVec4(0.65f, 0.80f, 1.00f, 1.00f);
colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
colors[ImGuiCol_FrameBgActive]       = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

colors[ImGuiCol_TitleBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.50f); // Transparent title bar
colors[ImGuiCol_TitleBgActive]       = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

colors[ImGuiCol_PopupBg]             = ImVec4(0.95f, 0.95f, 1.00f, 1.00f); // Soft white popup

colors[ImGuiCol_ScrollbarBg]         = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
colors[ImGuiCol_ScrollbarGrab]       = ImVec4(0.60f, 0.70f, 1.00f, 0.8f);
colors[ImGuiCol_ScrollbarGrabHovered]= ImVec4(0.50f, 0.60f, 0.90f, 0.9f);
colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.50f, 0.80f, 1.0f);

colors[ImGuiCol_SliderGrab]          = ImVec4(1.0f, 0.00f, 0.00f, 1.00f); // Red Slider
colors[ImGuiCol_SliderGrabActive]    = ImVec4(1.0f, 0.00f, 0.00f, 1.00f);

colors[ImGuiCol_Tab]                 = ImVec4(0.85f, 0.90f, 1.00f, 1.00f);
colors[ImGuiCol_TabHovered]          = ImVec4(0.65f, 0.80f, 1.00f, 1.00f);
colors[ImGuiCol_TabActive]           = ImVec4(0.45f, 0.70f, 1.00f, 1.00f);
//==========================================

     
style.ScaleAllSizes(std::max(1.0f, density / 150.0f));  
style.ScrollbarSize /= 1.4;


ImGui_ImplOpenGL3_NewFrame();  
ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);  
ImGui::NewFrame();  
if (ImGuiOK) {  
    int touchCount = (((int (*)())(Class_Input__get_touchCount))());  
if (touchCount > 0) {  
    UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields(*)(int))(Class_Input__GetTouch))(0);  
    float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;  
    switch (touch.m_Phase) {  
        case TouchPhase::Began:  
        case TouchPhase::Stationary:  
            io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);  
            io.MouseDown[0] = true;  
            break;  
        case TouchPhase::Ended:  
        case TouchPhase::Canceled:  
            io.MouseDown[0] = false;  
            clearMousePos = true;  
            break;  
        case TouchPhase::Moved:  
            io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);  
            break;  
        default:  
            break;  
    }
  }
}


//Expire DevelopEye
/* ExpireDate exp;
    exp.setExpirationDate(10,6,2026);//d,m,y
    if (exp.isExpired()) {
    ImGui::SetNextWindowSize(ImVec2(glWidth/3.5, glHeight/1.5), ImGuiCond_FirstUseEver);
    ImGui::Begin(OBFUSCATE("DevelopEye Mods V1 ️"));
    ImGui::Text(OBFUSCATE("DevelopEye Mods V1 Expired"));
    OpenURL(Il2CppString::Create("https://telegram.me/DevelopEyeTutorials"));
} */

DrawESP(g_GlWidth, g_GlHeight);
//ImGuiIO& io = ImGui::GetIO();



// UI Start
ImGui::SetNextWindowSize(ImVec2(750, 550), ImGuiCond_Always);
ImGui::Begin(OBFUSCATE(ICON_FA_CREDIT_CARD " DevelopEye Mods V1"), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize); // ImGuiWindowFlags_NoCollapse
/* ImVec2 childSize = ImGui::GetContentRegionAvail();  
ImGui::BeginChild("DevelopEye", childSize, true, ImGuiWindowFlags_AlwaysVerticalScrollbar); */

static int selectedWindow = 1; 
float time = ImGui::GetTime() * 8.0f;
ImVec4 activeColor = ImVec4(sin(time) * 0.5f + 0.5f, 
sin(time + 2.0f) * 0.5f + 0.5f, 
sin(time + 4.0f) * 0.5f + 0.5f, 1.0f);
ImVec4 safeColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  //Hack Off Text Color

ImGui::Separator();


if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
if (selectedWindow > 1) selectedWindow--;
}
ImGui::SameLine();
ImGui::Text(OBFUSCATE(ICON_FA_HEARTBEAT ""));
ImGui::SameLine();
if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
if (selectedWindow < 3) selectedWindow++;
}

if (selectedWindow == 1) {
ImGui::Columns(2, nullptr, false);    
static float t = 0.0f;
t += 0.10f;
ImVec4 activeColor = ImVec4(
    sin(t) * 0.5f + 0.5f,
    sin(t + 2) * 0.5f + 0.5f,
    sin(t + 4) * 0.5f + 0.5f,
    1.0f
);
ImVec4 safeColor = ImVec4(1, 1, 1, 1);


ImGui::Separator();

DevelopEyeMods::Toggle(OBFUSCATE("   Aimbot   "), &DevelopEyeAimbot); //Headshot
ImGui::SameLine();
if (DevelopEyeAimbot) {
ImGui::SameLine();
ImGui::TextColored(activeColor, OBFUSCATE("  [ ON ]"));
} else {
ImGui::SameLine();
ImGui::TextColored(safeColor, OBFUSCATE("  [ OFF ]"));
}

ImGui::Separator();




//ImGui::Separator();

// Checkboxes with Toggle ON/OFF Status
ImGui::Checkbox(OBFUSCATE(" Enable Esp"), &Enable);
ImGui::Checkbox(OBFUSCATE(" Esp Line"), &Config.ESP.Line);
ImGui::Checkbox(OBFUSCATE(" Esp Box"), &Config.ESP.Box);
ImGui::NextColumn();
ImGui::Checkbox(OBFUSCATE(" ESP Health"), &Config.ESP.Health);
ImGui::Checkbox(OBFUSCATE(" ESP Info"), &Config.ESP.Info);
ImGui::Columns(1);
// Window 1 Stop


ImGui::NewLine();

// Centered Text Calculation
/* float windowWidth = ImGui::GetWindowSize().x;
float textWidth = ImGui::CalcTextSize("Exp: Days: 000 Hours: 00 Min: 00 Sec: 00").x;
float centerPosX = (windowWidth - textWidth) * 0.5f;
ImGui::SetCursorPosX(centerPosX); 
ImGui::Text(OBFUSCATE("Exp :>"));
ImGui::SameLine();
ImGui::TextColored(dayColor, OBFUSCATE(" Days: %d "), days);
ImGui::SameLine();
ImGui::TextColored(hourColor, OBFUSCATE(" Hours: %d "), hours);
ImGui::SameLine();
ImGui::TextColored(minColor, OBFUSCATE(" Min: %d "), minutes);
ImGui::SameLine();
ImGui::TextColored(secColor, OBFUSCATE(" Sec: %d "), seconds); */

ImVec2 windowSize = ImGui::GetWindowSize();
float textWidth1 = ImGui::CalcTextSize(ICON_FA_CODE " DevelopEye ").x;
t += 0.10f; // Speed increased
ImVec4 rgbColor = ImVec4(sin(t) * 0.5f + 0.5f, sin(t + 2) * 0.5f + 0.5f, sin(t + 4) * 0.5f + 0.5f, 1.0f);
ImGui::SetCursorPosX((windowSize.x - textWidth1) * 0.5f);
ImGui::TextColored(rgbColor, OBFUSCATE(ICON_FA_CODE " DevelopEye "));
}
// Window 2
if (selectedWindow == 2) {
ImGui::Columns(2, nullptr, false);    
// RGB Animation Variables
static float t = 0.0f;
t += 0.10f; // RGB Speed
// Generate RGB Color
ImVec4 activeColor = ImVec4(
    sin(t) * 0.5f + 0.5f,
    sin(t + 2) * 0.5f + 0.5f,
    sin(t + 4) * 0.5f + 0.5f,
    1.0f
);

ImGui::Separator();

// Aim FOV Slider with Status
ImGui::Text(OBFUSCATE("Aim FOV"));
ImGui::SliderFloat("##Fov", &Fov_Aim, 0.f, 500.f);
ImGui::Separator();
/*ImGui::SameLine();
ImGui::TextColored(activeColor, OBFUSCATE("[ Value: %.3f ]"), Fov_Aim); */
ImGui::Checkbox(OBFUSCATE(" Aim Fire"), &AimWhen2);
ImGui::NextColumn();
ImGui::Checkbox(OBFUSCATE(" Aim Silent"), &AimSilent);
ImGui::Columns(1);

ImGui::NewLine();
// Update animation pulse
// At top of file (only once)
ImVec2 windowSize = ImGui::GetWindowSize();
float textWidth1 = ImGui::CalcTextSize(ICON_FA_CODE " DevelopEye ").x;
t += 0.10f; // Speed increased
ImVec4 rgbColor = ImVec4(sin(t) * 0.5f + 0.5f, sin(t + 2) * 0.5f + 0.5f, sin(t + 4) * 0.5f + 0.5f, 1.0f);
ImGui::SetCursorPosX((windowSize.x - textWidth1) * 0.5f);
ImGui::TextColored(rgbColor, OBFUSCATE(ICON_FA_CODE " DevelopEye "));
}              
// Window 2
if (selectedWindow == 3) {
ImGui::Columns(2, nullptr, false);    
// Window 2 Start, RGB Animation Variables
static float t = 0.0f;
t += 0.10f; // RGB Speed
// Generate RGB Color
ImVec4 activeColor = ImVec4(
    sin(t) * 0.5f + 0.5f,
    sin(t + 2) * 0.5f + 0.5f,
    sin(t + 4) * 0.5f + 0.5f,
    1.0f
);
ImVec4 safeColor = ImVec4(1, 1, 1, 1); // Normal White

ImGui::Separator();

//ImGui::Checkbox((std::string(ICON_FA_HEARTBEAT) + " Gold Body [Lobby]").c_str(), &goldbody);
//ImGui::Checkbox((std::string(ICON_FA_FIGHTER_JET) + " Black Body [Lobby]").c_str(), &blackbody);
ImGui::Checkbox(OBFUSCATE(" Speed Joystick"), &speedrun);
ImGui::Checkbox(OBFUSCATE(" Running Medi"), &rnmedi);
ImGui::Checkbox(OBFUSCATE(" Double Gun"), &doublegun);
//ImGui_v_Menu(5, OBFUSCATE(" Night Mode"), &NightM);
ImGui::NextColumn();
ImGui_v_Menu(2, OBFUSCATE(" Bypass V1"), &BypassA);
ImGui_v_Menu(3, OBFUSCATE(" Bypass V2"), &BypassB);
ImGui_v_Menu(4, OBFUSCATE(" Bypass V3"), &BypassC);
ImGui::Columns(1);

}

ImGui::End();
// UI End
ImGui::EndFrame();  
ImGui::Render();  
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
return old_eglSwapBuffers(dpy, surface);

}

typedef unsigned long DWORD;
static uintptr_t libBase;

uintptr_t string2Offset(const char *c) {
    int base = 16;
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}
/*
bool (*Bypass)(void *thiz);
bool _Bypass(void *thiz)
{
 return false;

}*/

inline void hack_injec();
inline void StartGUI() {
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (NULL != ptr_eglSwapBuffer) {
        DobbyHook((void *)ptr_eglSwapBuffer, (void*)hook_eglSwapBuffers, (void**)&old_eglSwapBuffers);
            LOGD("Gui Started");
			hack_injec();
        }
    }

bool libLoaded = false;

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, OBFUSCATE("/proc/self/maps"));

    fp = fopen(filename, OBFUSCATE("rt"));
    if (fp == NULL) {
        perror(OBFUSCATE("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}
ProcMap unityMap, anogsMap, il2cppMap;
using KittyScanner::RegisterNativeFn;


void hack() {
     LOGD("Inject Ok");
    //std::thread thread_hack(hack_thread, getpid());
    //thread_hack.detach();
    
}
uintptr_t get_symbol_addr_in_pid(pid_t pid, const char* libname, uintptr_t offset_in_lib) {
    char maps_path[64];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);

    FILE* fp = fopen(maps_path, "r");
    if (!fp) return 0;

    char line[512];
    uintptr_t base = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libname)) {
            sscanf(line, "%lx-%*lx", &base);
            break;
        }
    }
    fclose(fp);

    if (base == 0) return 0;
    return base + offset_in_lib;
}



    
pid_t get_pid_by_name(const char* process_name) {
    DIR* proc_dir = opendir("/proc");
    if (!proc_dir) return -1;

    struct dirent* entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        if (entry->d_type != DT_DIR) continue;

        pid_t pid = atoi(entry->d_name);
        if (pid <= 0) continue;

        char cmdline_path[256];
        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", pid);

        FILE* fp = fopen(cmdline_path, "r");
        if (!fp) continue;

        char cmdline[256];
        fgets(cmdline, sizeof(cmdline), fp);
        fclose(fp);

        if (strstr(cmdline, process_name)) {
            closedir(proc_dir);
            return pid;
        }
    }

    closedir(proc_dir);
    return -1;
}

void writeLog(const std::string& logMessage, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app); // Mở file ở chế độ append (thêm)
    if (outFile.is_open()) {
        outFile << logMessage << std::endl;
        outFile.close();
    } else {
        std::cerr << "Không thể mở file log: " << filename << std::endl;
    }
}

bool is_current_process(const char* target_name) {
    char cmdline_path[64];
    snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", getpid());

    FILE* fp = fopen(cmdline_path, "r");
    if (!fp) return false;

    char cmdline[256] = {0};
    fgets(cmdline, sizeof(cmdline), fp);
    fclose(fp);

    return strcmp(cmdline, target_name) == 0;
}

void hack_injec() {
	while (!unityMap.isValid()) {
        unityMap = KittyMemory::getLibraryBaseMap("libunity.so");
		anogsMap = KittyMemory::getLibraryBaseMap("libanogs.so");
		il2cppMap = KittyMemory::getLibraryBaseMap("libil2cpp.so");
        sleep(6);
	}
 sleep(5);
    Il2CppAttach();


//Bypass
//hexPatches.Bypass1 = MemoryPatch::createWithHex(getAbsoluteAddress("libil2cpp.so", 0x5ed140c),"20 00 80 D2 C0 03 5F D6");
//MemoryPatch::createWithHex(getAbsoluteAddress("libGGP.so", 0x5B92F0), "00 00 80 D2 C0 03 5F D6");
//hexPatches.NightM = MemoryPatch::createWithHex(getAbsoluteAddress("libunity.so", 0xCCBD10),"20 00 80 D2 C0 03 5F D6");


DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateBehavior"), 2), (void *) _LateUpdate, (void **) &LateUpdate);
//aimsilent
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateRotation"), 2), (void *) hook_mrAimSilent, (void **)&orig_mrSilentAim);
// Speed Run
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFoldWingGliding"), 0), (void *) _IsFoldWingGliding, (void **)& IsFoldWingGliding);
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("LLOABGDLMGK"), OBFUSCATE("LEBIPIGPEEP"), 1), (void *) _LEBIPIGPEEP, (void **)& LEBIPIGPEEP);
// ResetGuest
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameConfig") , OBFUSCATE("get_ResetGuest"), 0), (void *) ResetGuest, (void **) &_ResetGuest);
//Double Gun
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Weapon"), OBFUSCATE("GetCombineType"), 0), (void *) _GetCombineType, (void **)& GetCombineType);
//Black Body
//DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("UMA"), OBFUSCATE("TextureMerge"), OBFUSCATE("SetupModule"), 2), (void *) _SetupModule, (void **)& SetupModule);
//Gold Body
//DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsGod"), 0), (void *) _get_IsGod, (void **) &get_IsGod);
//Medi in Run
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerSkillEatFaster"), OBFUSCATE("OnPreparationCancel"), 1), (void *) _OnPreparationCancel, (void **)& OnPreparationCancel);
//Fast Switch
//DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_InSwapWeaponCD"), 0), (void *) _get_InSwapWeaponCD, (void **) &get_InSwapWeaponCD);

//Reset Guest
MemoryPatch::createWithHex((uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameConfig"), OBFUSCATE("get_ResetGuest"), 0), OBFUSCATE("20 00 80 D2 C0 03 5F D6")).Modify();
hexPatches.Guest = MemoryPatch::createWithHex(getAbsoluteAddress("libil2cpp.so", 0x5ed140c),"20 00 80 D2 C0 03 5F D6");

//OpenURL = (void (*)(String *))Il2CppGetMethodOffset("UnityEngine.CoreModule.dll","UnityEngine","Application","OpenURL",1); //Expire DevelopEye
ImGuiOK = true;
}


void hack_thread(pid_t pid) {
	StartGUI();
	while(pid == -1){pid = get_pid_by_name("com.dts.freefireth");} 
	remote_inject(pid);
	writeLog(to_string(pid));
}
__attribute__((constructor))
void lib_main()
{
    std::thread thread_hack(hack_thread, get_pid_by_name("com.dts.freefireth"));
    thread_hack.detach();
}

// REGISTER_ZYGISK_MODULE (MyModule)

