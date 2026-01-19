#pragma once

#include <wx/wx.h>

namespace genid
{

    class Application : public wxApp {
    public:
        virtual bool OnInit();
    };

}