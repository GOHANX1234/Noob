#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <Il2Cpp.h>
#include <Tools.h>
#include <Vector3.hpp>
#include <Color.h>
bool menu = true;
bool menu1 = false;
bool menu2 = false;
bool menu3 = false;
bool menu4 = false;
bool DevelopEyeAimbot = false; //Headshot
#include "obfuscate.h"
#include "Unity/unity.h"
#include "Class.h"
#include "Rect.h"
//inline static int g_GlHeight, g_GlWidth;
#include "Bools.h"
#include <math.h>
#include <stdio.h>
inline static int g_GlHeight, g_GlWidth;
typedef char PACKAGENAME;
//#include "MemoryPatch.h"
// Khai Báo
#define ICON_MIN_FA 0xf000
#define ICON_MAX_FA 0xf957
// Master ESP colors
ImVec4 normalESPColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // White
ImVec4 knockedESPColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red

// Unified color selector
ImColor GetESPColor(bool isKnocked) {
    ImVec4 c = isKnocked ? knockedESPColor : normalESPColor;
    return ImColor(c.x * 255, c.y * 255, c.z * 255, c.w * 255);
}
#define ICON_FA_CROWN "\xef\x94\xa5"
#define ICON_FA_USER_NINJA "\xef\x94\x93"
#define ICON_FA_BOLT "\xef\x83\xa7"
#define ICON_FA_SKULL "\xef\x95\x8c"
#define ICON_FA_GHOST "\xef\x9b\xa2"
#define ICON_FA_DRAGON "\xf6\x96"
#define ICON_FA_FIRE "\xef\x81\xad"
#define ICON_FA_MASK "\xef\x9b\xba"
ImVec4 colorDistance = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 colorTextBackground = ImVec4(0, 0, 0, 255);
struct cfg {
    bool aimbot;
    int aim_type = 0;
    int aim_target = 1;
    struct _esp {
	//	bool inforohan = false
        bool Box = false;
        bool Box3D = false;
        bool Line = false;
		bool Info = false;
        bool Health = false;
        bool Distance = false;
        bool IsName = false;
        bool Path = false;
        bool Esp360 = false;
        bool Target = false;
    }ESP;
}inline Config;
bool AimWhen3 = false;
bool AimWhen2 = false;
bool box = false;
bool AimWhen1 = false;
bool EspLol = true;
//bool fastSwitch = false;
bool doublegun = false;
//bool blackbody = false;
//bool goldbody = false;
bool rnmedi = false;
bool showbox1 = false;
bool showline1 = false;
bool showline2 = false;
bool AimSilent = false;
bool camcao = false;
bool showline = false;
bool speedrun = false;
bool Firewall = true;
bool health = false;

//int showline = 0;
const char* line[] = {OBFUSCATE("Esp Line 1"),OBFUSCATE("Esp Line 2"),OBFUSCATE("Esp Line 3")};

int showbox = 1;
//MemoryPatch  Resetguest,DouleGun,nightmod,WallHack2;

//const char* box[] = {OBFUSCATE("Esp Box"),OBFUSCATE("Esp Box 3D")};

struct sColor {
        float circle[4] = {0 / 255.0f, 255 / 255.0f, 0 / 255.0f, 255 / 255.0f};

		float box[4] = {255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f};
        float line1[4] = {255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f};
        float box1[4] = {255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f};
        float box3d1[4] = {255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f};
        float info1[4] = {0 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f};

        float line2[4] = {255 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f};
        float box2[4] = {255 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f};
        float box3d2[4] = {255 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f};
        float info2[4] = {255 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f};
};
sColor Color;
bool Reset = false;



bool isOutsideScreen(ImVec2 pos, ImVec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

ImVec2 pushToScreenBorder(ImVec2 Pos, ImVec2 screen, int offset) {
    int x = (int) Pos.x;
    int y = (int) Pos.y;
    
    if (Pos.y < 0) {
        y = -offset;
    }
    
    if (Pos.x > screen.x) {
        x = (int) screen.x + offset;
    }
    
    if (Pos.y > screen.y) {
        y = (int) screen.y + offset;
    }
    
    if (Pos.x < 0) {
        x = -offset;
    }
    return ImVec2(x, y);
}

static float tm = 127 / 255.f;

void(*Set_Aim)(void* _this);
void _Set_Aim(void* _this) {
    return;
    return Set_Aim(_this);
}

// BYPASS
bool(*Bypass)(void* bypass); 
bool _Bypass(void* bypass) { 
    return false;
}

bool(*FixGame)(void* _this);
bool _FixGame(void* _this) {
    if (_this != NULL) {
        return true;
    }
}

bool(*BypassESP)(void* _this);
bool _BypassESP(void* _this) {
    return true;
}

bool(*Bypass2)(void* _this);
bool _Bypass2(void* _this) {
    return true;
}


//Expire DevelopEye
/* class ExpireDate {
public:
    ExpireDate() {
        std::time_t now = std::time(nullptr);
        expirationTime = std::chrono::system_clock::from_time_t(now);
    }
    void setExpirationDate(int day, int month, int year) {
        std::tm tm_struct = {};
        tm_struct.tm_mday = day;
        tm_struct.tm_mon = month - 1;
        tm_struct.tm_year = year - 1900;
        std::time_t expirationTime_t = std::mktime(&tm_struct);
        expirationTime = std::chrono::system_clock::from_time_t(expirationTime_t);
    }
    bool isExpired() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        return now >= expirationTime;
    }
private:
    std::chrono::system_clock::time_point expirationTime;
}; */



void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}

void drawText2(int x, int y, long color, const char *str, float size) {
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
}

void DrawRectFilled(int x, int y, int w, int h, ImColor color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void DrawRectFilledHealth(int x, int y, int w, int h, ImVec4 color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int T) {
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), color);
}

void DrawHealths(Rect box, float entityHealth, float maxHealth, int TeamID, const char* name, long color) {
    float x = box.x - (140 - box.w) / 2;
    float y = box.y;
    char dis[20];
    // sprintf(dis, "%0.fM", d);

    char TeamText[20];
    sprintf(TeamText, "%d", (int)TeamID);
    ImVec4 HPColor = ImVec4{1, 1, 0, 127 / 255.f}; // Màu mặc định cho máu

    if (entityHealth < maxHealth) {
        float healthPercentage = entityHealth / maxHealth;

        if (healthPercentage < 0.3f) {
            HPColor = ImVec4{0.5f, 0.0f, 0.0f, 127 / 255.f}; // Màu đỏ cho máu thấp
        } else if (healthPercentage < 0.6f) {
            HPColor = ImVec4{1, 0, 0, 127 / 255.f}; // Màu cam cho máu trung bình
        }
    }

    tm = 100.f / 255.f;
    DrawRectFilled(x - strlen(name), y - 41, 120 + strlen(name) * 2, 20, color); // Đám mây nền cho tên người chơi
    tm = 255.f / 255.f;
    DrawRectFilled(x - strlen(name), box.y - 41, 25, 20, color);
    if (strlen(TeamText) < 2) {
        drawText2(x + 6 - strlen(name), box.y - 42, ImColor(255,255,255), TeamText, 18.943);
    } else {
        drawText2(x - strlen(name), box.y - 42, ImColor(255,255,255), TeamText, 18.943);
    }
    drawText2(x + 28 - strlen(name), y - 43, ImColor(255,255,255), name, 18.943);
    float maxWidth = 120; // Độ dài tối đa của thanh máu
    float healthBarWidth = entityHealth * maxWidth / maxHealth; // Độ dài thanh máu dựa trên tỷ lệ máu hiện tại và máu tối đa
    DrawRectFilledHealth(x - maxWidth / 2, y - 18, healthBarWidth, 8, HPColor);// cập nhật vị trí và kích thước của thanh máu
    drawText2(x + 125 + strlen(name), y - 43, ImColor(255,255,255), dis,18.943);
    DrawTriangle(box.x + box.w / 2 - 10, y - 8, box.x + box.w / 2 + 15 - 10, y - 8, box.x + box.w / 2 - 2, y, ImColor(255,255,255), 1);
}

static float SetFieldOfView = 0, GetFieldOfView = 0;

float (*get_deltaTime)();
float smoothSpeedAIM = 5; 
void *MyPlayer = NULL;
bool Drone;

const float RADAR_SIZE = 200.0f; // kích thước của radar
const ImVec2 RADAR_CENTER(100.0f, 100.0f); // tọa độ trung tâm của radar

float x,y;
float enemy1 = 2.0f;

inline void DrawAIMBOT(float screenWidth, float screenHeight) { 
}

void DroneView() {
    if (GetFieldOfView == 0) {
        GetFieldOfView = get_fieldOfView();
    }
    if (SetFieldOfView > 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView + SetFieldOfView);
    }
    if (SetFieldOfView == 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView);
    }
}

Quaternion GetRotationToTheLocation(Vector3 Target, float Height, Vector3 MyEnemy) {
return Quaternion::LookRotation((Target + Vector3(0, Height, 0)) - MyEnemy, Vector3(0, 1, 0));
}

bool isVisible(void *enemy)  {
    if(enemy != NULL)  {
         void *hitObj = NULL;
         auto Camera = Transform_GetPosition(Component_GetTransform(Camera_main()));
         auto Target = Transform_GetPosition(Component_GetTransform(Player_GetHeadCollider(enemy)));
         return !Physics_Raycast(Camera, Target, 12, &hitObj);
    }
    return false;
}

void *GetClosestEnemy() {
    float shortestDistance = 9999;
    void* closestEnemy = NULL;   
     
    void* get_MatchGame = Curent_Match();
    void* LocalPlayer = GetLocalPlayer(get_MatchGame);

    if (LocalPlayer != NULL && get_MatchGame != NULL && Enable && get_MatchGame) {
        monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)get_MatchGame + ListPlayer);
        
        for (int u = 0; u < players->getNumValues(); u++) {
            void* Player = players->getValues()[u]; 
            if (Player != NULL && !get_isLocalTeam(Player) && !get_IsDieing(Player) && get_isVisible(Player) && get_MaxHP(Player)) {    
                Vector3 PlayerPos = getPosition(Player);
                Vector3 LocalPlayerPos = getPosition(LocalPlayer);
                Vector3 pos2 = WorldToScreenPoint(Camera_main(), PlayerPos);
                bool isFov1 = isFov(Vector3(pos2.x, pos2.y), Vector3(g_GlWidth / 2, g_GlHeight / 2), Fov_Aim);
            
                
                
                
                float distance = Vector3::Distance(LocalPlayerPos, PlayerPos);
                if (distance < 1000) {
                    Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
                    float angle = Vector3::Angle(targetDir, GetForward(Component_GetTransform(Camera_main()))) * 100.0;             
            
                    if (angle <= Fov_Aim && isFov1 && angle < shortestDistance) {
                     if(isVisible(Player)) {
                        shortestDistance = angle;
                        closestEnemy = Player;
                    }
                   }
                }
            }
        }
    }
    return closestEnemy;
}


//Headshot
void* GetBestVisibleEnemy(void* local, void* match) {
    void* bestEnemy = nullptr;
    float minAngle = 9999.0f;

    if (!local || !match) return nullptr;

    auto* players = *(monoDictionary<uint8_t*, void**>**)((uintptr_t)match + ListPlayer);
    if (!players) return nullptr;

    Vector3 localPos = getPosition(local);
    Vector3 camForward = GetForward(Component_GetTransform(Camera_main()));

    for (int i = 0; i < players->getNumValues(); i++) {
        void* player = players->getValues()[i];
        if (!player || get_isLocalTeam(player) || get_IsDieing(player) || get_MaxHP(player) <= 0) continue;
        if (!isVisible(player)) continue;

        Vector3 enemyPos = getPosition(player);
        float dist = Vector3::Distance(localPos, enemyPos);
        if (dist > 99999.0f) continue;

        Vector3 screen = WorldToScreenPoint(Camera_main(), enemyPos);
        bool insideFov = isFov(Vector3(screen.x, screen.y), Vector3(g_GlWidth / 2, g_GlHeight / 2), Fov_Aim);
        if (!insideFov) continue;

        Vector3 dir = Vector3::Normalized(enemyPos - localPos);
        float angle = Vector3::Angle(dir, camForward) * 100.0f;

        if (angle < minAngle) {
            minAngle = angle;
            bestEnemy = player;
        }
    }
    return bestEnemy;
}
void (*LateUpdate)(void* Player);
void _LateUpdate(void* Player) {
    if (!Player || !DevelopEyeAimbot) {
        LateUpdate(Player);
        return;
    }
    void* match = Curent_Match();
    void* local = GetLocalPlayer(match);
    if (!match || !local) {
        LateUpdate(Player);
        return;
    }
    void* enemy = GetBestVisibleEnemy(local, match);
    if (!enemy) {
        LateUpdate(Player);
        return;
    }
    Vector3 enemyHead = GetHeadPosition(enemy);
    Vector3 localCam = CameraMain(local);
    Quaternion aimRot = GetRotationToTheLocation(enemyHead, 0.045f, localCam);

    bool isFiring = get_IsFiring(local);

    if (AimWhen2 && isFiring) {
        set_aim(local, aimRot);
    } else if (!AimWhen2) {
        set_aim(local, aimRot);
    }
    LateUpdate(Player);
}




void (*orig_mrSilentAim)(void *, float, float);
void hook_mrAimSilent(void *_this, float a1, float a2) {
if (_this != nullptr) {
if(Enable) {
if (AimSilent) {
void *CurrentMatch = Curent_Match();
if (CurrentMatch != NULL) {
void* LocalPlayer = GetLocalPlayer(CurrentMatch);
if (LocalPlayer != NULL)  {
bool visible = isVisible(LocalPlayer);
if (visible) {
if (get_IsFiring(GetLocalPlayer(CurrentMatch))) {
return;
} else {
orig_mrSilentAim(_this, a1, a2);
}
}
}
}
}
}
orig_mrSilentAim(_this, a1, a2);
}
}
	
inline void DrawESP(float screenWidth, float screenHeight) {
    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    if (!draw) return;

        

        if (Enable) {
        void* current_Match = Curent_Match();
        void* local_player = GetLocalPlayer(current_Match);

        if (local_player && current_Match) {
            auto* players = *(monoDictionary<uint8_t*, void**>**)((long)current_Match + ListPlayer);
            void* camera = Camera_main();

            if (players && camera) {
                for (int u = 0; u < players->getNumValues(); u++) {
                    void* closestEnemy = players->getValues()[u];
                    if (closestEnemy != local_player && closestEnemy && get_isVisible(closestEnemy) && !get_isLocalTeam(closestEnemy)) {
                        Vector3 Toepos = getPosition(closestEnemy);
                        Vector3 Toeposi = WorldToScreenPoint(camera, Toepos);
                        if (Toeposi.z < 1) continue;

                        Vector3 HeadPos = getPosition(closestEnemy) + Vector3(0, 1.9f, 0);
                        Vector3 HeadPosition = WorldToScreenPoint(camera, HeadPos);
                        if (HeadPosition.z < 1) continue;

                        draw->AddCircle(ImVec2(screenWidth / 2, screenHeight / 2), Fov_Aim, ImColor(255, 255, 255), 0, 1.5f);

                        float distance = Vector3::Distance(getPosition(local_player), Toepos);
                        float Height = abs(HeadPosition.y - Toeposi.y) * (1.2 / 1.1);
                        float Width = Height * 0.50f;
                        Rect rect = Rect(HeadPosition.x - Width / 2.f, screenHeight - HeadPosition.y, Width, Height);

                        if (Config.ESP.Line) {
                         if(get_IsDieing(closestEnemy)) {
                            draw->AddLine(ImVec2(screenWidth / 2, 80), ImVec2(rect.x + rect.w / 2, rect.y + rect.h / 35), ImColor(255, 0, 0), 1.7);
                          } else {
                            draw->AddLine(ImVec2(screenWidth / 2, 80), ImVec2(rect.x + rect.w / 2, rect.y + rect.h / 35), ImColor(255, 255, 255), 1.7);
                        }

                if (Config.ESP.Box) {
    int x = rect.x;
    int y = rect.y;
    int _width = rect.w;
    int _height = rect.h;

    if (get_IsDieing(closestEnemy)) {
        // Keep original red box for dying enemies
        draw->AddRect(ImVec2(x, y), ImVec2(x + _width, y + _height), ImColor(255, 0, 0), visual_esp_box, 0, visual_esp_boxth);
    } else {
        // New corner-style box for alive enemies
        ImColor color = ImColor(255, 255, 255);
        float thickness = visual_esp_boxth;

        // Top corners
        draw->AddLine(ImVec2(x, y), ImVec2(x + 10, y), color, thickness); // Top-left horizontal
        draw->AddLine(ImVec2(x, y), ImVec2(x, y + 10), color, thickness); // Top-left vertical
        draw->AddLine(ImVec2(x + _width, y), ImVec2(x + _width - 10, y), color, thickness); // Top-right horizontal
        draw->AddLine(ImVec2(x + _width, y), ImVec2(x + _width, y + 10), color, thickness); // Top-right vertical

        // Bottom corners
        draw->AddLine(ImVec2(x, y + _height), ImVec2(x + 10, y + _height), color, thickness); // Bottom-left horizontal
        draw->AddLine(ImVec2(x, y + _height), ImVec2(x, y + _height - 10), color, thickness); // Bottom-left vertical
        draw->AddLine(ImVec2(x + _width, y + _height), ImVec2(x + _width - 10, y + _height), color, thickness); // Bottom-right horizontal
        draw->AddLine(ImVec2(x + _width, y + _height), ImVec2(x + _width, y + _height - 10), color, thickness); // Bottom-right vertical
    }

    // Health Bar (keep your original logic for dying state)
    int xx = rect.x + rect.w + 2;
    int yy = rect.y;

    if (get_IsDieing(closestEnemy)) {
        if (Config.ESP.Health) {
            draw->AddRectFilled(ImVec2(xx, yy), ImVec2(xx + 5, yy + rect.h), ImColor(0, 0, 0, 255));
            draw->AddRectFilled(ImVec2(xx + 1, yy + rect.h - (rect.h * ((float)GetHp(closestEnemy) / get_MaxHP(closestEnemy)))), ImVec2(xx + 4, yy + rect.h), die);
        }
    } else {
        if (Config.ESP.Health) {
            float maxHealth = get_MaxHP(closestEnemy);
            float currentHealth = GetHp(closestEnemy);
            float healthPercentage = currentHealth / maxHealth;

            ImVec4 healthColor = ImLerp(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f - healthPercentage);

            float barWidth = 5.0f;
            float barHeight = rect.h * healthPercentage;

            ImVec2 barPos(xx + 1, yy + rect.h - barHeight);
            ImVec2 barEnd(xx + 4, yy + rect.h);

            draw->AddRectFilled(ImVec2(xx, yy), ImVec2(xx + barWidth, yy + rect.h), ImColor(0, 0, 0, 255)); // black bg
            draw->AddRectFilled(barPos, barEnd, ImColor(healthColor)); // health fill
            draw->AddRect(ImVec2(xx, yy), ImVec2(xx + barWidth, yy + rect.h), IM_COL32(255, 255, 255, 255)); // white border
        }
    }

        
	                    

                 if (Config.ESP.Info) {
    monoString* Nick = get_NickName(closestEnemy);
    std::string names;

    if (Nick != nullptr) {
        int len = Nick->getLength();
        for (int i = 0; i < len; i++) {
            char c = get_Chars(Nick, i);
            names += (isascii(c) && isprint(c)) ? c : '?';
        }

        float smallSize = 12.0f;
        float scale = smallSize / ImGui::GetFontSize();

        ImVec2 baseNameSize = ImGui::CalcTextSize(names.c_str());
        ImVec2 nameSize = ImVec2(baseNameSize.x * scale, baseNameSize.y * scale);

        float nameX = rect.x + (rect.w / 2.0f) - (nameSize.x / 2.0f);
        float nameY = rect.y - nameSize.y - 5.0f;

        ImU32 textColor = GetESPColor(get_IsDieing(closestEnemy));
        ImU32 shadowColor = IM_COL32(0, 0, 0, 200);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx != 0 || dy != 0)
                    draw->AddText(ImGui::GetFont(), smallSize, ImVec2(nameX + dx, nameY + dy), shadowColor, names.c_str());
            }
        }
        draw->AddText(ImGui::GetFont(), smallSize, ImVec2(nameX, nameY), textColor, names.c_str());
    }

    // === Distance Below Box ===
    char distText[32];
    snprintf(distText, sizeof(distText), "%.2fm", distance);

    float smallSize = 12.0f;
    float scale = smallSize / ImGui::GetFontSize();

    ImVec2 baseDistSize = ImGui::CalcTextSize(distText);
    ImVec2 distSize = ImVec2(baseDistSize.x * scale, baseDistSize.y * scale);

    float distX = rect.x + (rect.w / 2.0f) - (distSize.x / 2.0f);
    float distY = rect.y + rect.h + 5.0f;

    ImU32 textColor = GetESPColor(get_IsDieing(closestEnemy));
    ImU32 shadowColor = IM_COL32(0, 0, 0, 200);

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0)
                draw->AddText(ImGui::GetFont(), smallSize, ImVec2(distX + dx, distY + dy), shadowColor, distText);
        }
    }
    draw->AddText(ImGui::GetFont(), smallSize, ImVec2(distX, distY), textColor, distText);
}

                        }
                    }
                }
            }
        //}
    }
}
}
}



	
//Speed Run
bool (*IsFoldWingGliding)(void *player);
bool _IsFoldWingGliding(void *player) {
	if (player != NULL) {
	    if(Enable) {
	        if (speedrun) {
		        return true;
            }
        }
	}
	return IsFoldWingGliding(player);
}

static int (*LEBIPIGPEEP)(...);
static int _LEBIPIGPEEP(void* GLDLCOBLGNF) {
	if(Enable) {
	    if (speedrun) {
	    	return 1;
    	}
    }
	return LEBIPIGPEEP(GLDLCOBLGNF);
}

bool (*ADBBMDMEFNO)(void *thiz);
bool _ADBBMDMEFNO(void *thiz) {
	if (thiz != NULL) {
	    if(Enable) {
	        if (speedrun) {
		        return true;
            }
        }
	}
	return _ADBBMDMEFNO(thiz);
}

//Black Body
/*bool (*SetupModule)(void *thiz);
bool _SetupModule(void *thiz) {
  if (blackbody) {
   return true;
  }
  return SetupModule(thiz);
}*/

//Gold Body
/* bool (*get_IsGod)(void *thiz);
bool _get_IsGod(void *thiz) {
  if (goldbody) {
   return true;
  }
  return get_IsGod(thiz);
} */

//Double gun
bool (*GetCombineType)(void *thiz);
bool _GetCombineType(void *thiz) {
    if (thiz != NULL) {
        if(Enable) {
            if (doublegun) {
                return true;
            }
        }
    }
    return _GetCombineType(thiz);
}


//Running Medi
bool (*OnPreparationCancel)(void *thiz);
bool _OnPreparationCancel(void *thiz) {
    if (thiz != NULL) {
        if(Enable) {
            if (rnmedi) {
                return true;
            }
        }
    }
    return _OnPreparationCancel(thiz);
}

//Fast switch
/* bool (*get_InSwapWeaponCD)(void *thiz);
bool _get_InSwapWeaponCD(void *thiz) {
  if (fastSwitch) {
   return true;
  }
  return get_InSwapWeaponCD(thiz);
} */

// Unlock Account
bool(*_ResetGuest)(void* _this);
bool ResetGuest(void* _this){
    if (_this != NULL) {
        if (Reset) {
            return true; 
            remove(OBFUSCATE("/storage/emulated/0/com.garena.msdk/guest100067.dat"));
        }
    }
}
