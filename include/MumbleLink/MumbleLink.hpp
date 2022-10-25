#pragma once

#include <Windows.h>
#include <cstdint>

class MumbleLink
{
private:
    struct MumbleContext
    {
        unsigned char serverAddress[28]; // contains sockaddr_in or sockaddr_in6
        uint32_t mapId;
        uint32_t mapType;
        uint32_t shardId;
        uint32_t instance;
        uint32_t buildId;
        // Additional data beyond the <context_len> bytes the game instructs Mumble to use to distinguish between instances.
        uint32_t uiState; // Bitmask: Bit 1 = IsMapOpen, Bit 2 = IsCompassTopRight, Bit 3 = DoesCompassHaveRotationEnabled, Bit 4 = Game has focus, Bit 5 = Is in Competitive game mode, Bit 6 = Textbox has focus, Bit 7 = Is in Combat
        uint16_t compassWidth; // pixels
        uint16_t compassHeight; // pixels
        float compassRotation; // radians
        float playerX; // continentCoords
        float playerY; // continentCoords
        float mapCenterX; // continentCoords
        float mapCenterY; // continentCoords
        float mapScale;
        uint32_t processId;
        uint8_t mountIndex;
    };
    struct LinkedMem
    {
        UINT32 uiVersion;
        DWORD uiTick;
        float fAvatarPosition[3];
        float fAvatarFront[3];
        float fAvatarTop[3];
        wchar_t name[256];
        float fCameraPosition[3];
        float fCameraFront[3];
        float fCameraTop[3];
        wchar_t identity[256];
        UINT32 context_len;
        unsigned char context[256];
        wchar_t description[2048];
    };
    LinkedMem *lm = nullptr;
    HANDLE mapObj = nullptr;

public:
    bool init()
    {
        mapObj = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(LinkedMem), L"MumbleLink");
        if (mapObj == nullptr) return false;
        lm = (LinkedMem *) MapViewOfFile(mapObj, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
        if (lm == nullptr)
        {
            CloseHandle(mapObj);
            mapObj = nullptr;
            return false;
        }
        return true;
    };

    inline UINT32 uiVersion()
    {
        return lm->uiVersion;
    }

    inline DWORD uiTick()
    {
        return lm->uiTick;
    }

    wchar_t *getName()
    {
        return lm->name;
    };

    wchar_t *getDescription()
    {
        return lm->description;
    };

    wchar_t *getIdentity()
    {
        return lm->identity;
    };

    unsigned int getContextLength()
    {
        return lm->context_len;
    }

    MumbleContext *getContext()
    {
        return reinterpret_cast<MumbleContext *>(lm->context);
    };

    float *getAvatarPosition()
    {
        return lm->fAvatarPosition;
    };

    float *getAvatarFront()
    {
        return lm->fAvatarFront;
    };

    float *getAvatarTop()
    {
        return lm->fAvatarTop;
    };

    float *getCameraPosition()
    {
        return lm->fCameraPosition;
    };

    float *getCameraFront()
    {
        return lm->fCameraFront;
    };

    float *getCameraTop()
    {
        return lm->fCameraTop;
    };

    void close()
    {
        if (mapObj != nullptr) CloseHandle(mapObj);
    };
};