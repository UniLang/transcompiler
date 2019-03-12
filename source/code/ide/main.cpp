#include "code/utilities/graphics/imgui/mechanics.hpp"
#include "code/utilities/graphics/imgui/sdl_init_settings.hpp"
#include "code/utilities/graphics/imgui/ui/ui_renders.hpp"
#include "code/utilities/graphics/imgui/ui/window/window_renderer.hpp"
#include "code/utilities/graphics/imgui/ui/draw/rectangle/rectangle_settings.hpp"
#include "code/utilities/graphics/imgui/ui/draw/mouse_events/mouse_events.hpp"
#include "code/utilities/graphics/imgui/ui/draw/mouse_events/mouse_events_checker.hpp"
#include "code/utilities/graphics/imgui/ui/draw/position.hpp"
#include "code/utilities/graphics/imgui/ui/draw/rectangle/rectangle_drawer.hpp"
#include "code/utilities/graphics/imgui/ui/draw/pixel/pixel_settings.hpp"
#include "code/utilities/graphics/imgui/ui/draw/pixel/pixel_drawer.hpp"
#include "code/utilities/graphics/imgui/ui/draw/full_color_bitmap/full_color_bitmap_drawer.hpp"
#include "code/transcompilers/unilang/tokens/get_tokens.hpp"
#include "code/transcompilers/unilang/language-and-theme-creator/font/unilang_font.hpp"
#include "code/utilities/types/char/lib.hpp"




struct ide_settings
{
    Sdl_Init_Settings init;
    All_Language_Tokens tokens;
    std::vector<Character_Segment> unilang_font;
    std::unordered_map<int,Character_Segment> unilang_font_lookup;
    Window_Settings method_item;
    
};

//other utilities
Position window_adjusted_position(Position pos)
{
    const ImVec2 screen_Position = ImGui::GetCursorScreenPos();
    Position     p;
    p.x = pos.x + screen_Position.x;
    p.y = pos.y + screen_Position.y;
    return p;
}

Position window_adjusted_position_top_left_corner()
{
        Position temp;
        temp.x = 0;
        temp.y = 0;
        auto pos = window_adjusted_position(temp);
        return pos;
}


std::vector<Character_Segment> str_to_bdf_segment(std::unordered_map<int,Character_Segment> const& c, std::string const& str){
    std::vector<Character_Segment> segments;
    for (auto const& it: str){
        auto lookup_char = static_cast<int>(it);
        segments.emplace_back(c.at(lookup_char));
    }
    return segments;
}


std::vector<Position> relative_positions_of_segment(Character_Segment const& segment){
    std::vector<Position> pos;
    
    Position p;
    p.x = 0;
    p.y = 0;
    for (auto const& it: segment.hex_encoded_bitmap){
            auto binary = Hex_To_4_Bit_Binary_Segments(it);
            for (auto const& b: binary){
                if (b == '1'){
                    pos.emplace_back(p);
                }
                p.x+= 1;
            }
            p.x=0;
            p.y+= 1;
    }
    return pos;
}

Full_Color_Bitmap bdf_segments_to_bitmap(std::vector<Character_Segment> const& segments){
    
    Full_Color_Bitmap bitmap;
    bitmap.color_fill.r = 0;
    bitmap.color_fill.g = 0;
    bitmap.color_fill.b = 0;
        
    std::vector<std::vector<Position>> relative_pos;
    for (auto const& it: segments){
        relative_pos.emplace_back(relative_positions_of_segment(it));
    }
    
    int total_x_offset = 0;
    int total_y_offset = 0;
    for (size_t i = 0; i < segments.size(); ++i){
        
        for (auto const& x: relative_pos[i]){
            Position pos;
            
            //start with the character's offset relative the other characters already typed
            pos.x = x.x + total_x_offset;
            pos.y = x.y + total_y_offset;
            
            //shift character based on bdf segment information
            pos.x += segments[i].bbo_x;
            pos.y -= segments[i].bb_h;
            pos.y -= segments[i].bbo_y;
            
            bitmap.pixels.emplace_back(pos);
        }
        
        //increment a soace offset for the next consecutive character box
        total_x_offset += segments[i].d_width_x;
        total_y_offset += segments[i].d_width_y;
    }
    
    return bitmap;
}



void each_frame(ide_settings & settings){
    
    Ui_Renders::render_main_menu_bar([](){
        if (ImGui::MenuItem("hello world", "T"))
        {
        }
    });
    
    // for testing
    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
    
    
    Window_Renderer::render(settings.method_item,[&](){
        
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        
        auto pos = window_adjusted_position_top_left_corner();
        pos.x += 10;
        pos.y += 10;
        
        
        
        
        std::string message_str = "abcdefghijklmnopqrstuvwxyz(){}[]!@#$%^&*1234567890-iiiijijijijijijijij";
        auto message = str_to_bdf_segment(settings.unilang_font_lookup,message_str);
        auto bitmap = bdf_segments_to_bitmap(message);
        
        
        //some pixel guessing
        const auto EXPECTED_MONOSPACE_CHAR_WIDTH = 6;
        const auto EXPECTED_MONOSPACE_FITTING_HEIGHT = 15;
        const auto SOME_BUFFER_SPACE = 3;
        
        Rectangle_Settings rec2;
        rec2.width     = (message_str.size() * EXPECTED_MONOSPACE_CHAR_WIDTH) + SOME_BUFFER_SPACE;
        rec2.height    = EXPECTED_MONOSPACE_FITTING_HEIGHT;
        rec2.thickness = 1;
        rec2.rounding  = 0.0;
        rec2.color_border.r = 0;
        rec2.color_border.g = 0;
        rec2.color_border.b = 0;
        rec2.color_fill.r = 50;
        rec2.color_fill.g = 205;
        rec2.color_fill.b = 50;
        
        pos.y -= 10;
        pos.x -= 2;
        Rectangle_Drawer::draw_rectangle(draw_list,pos,rec2);
        pos.y += 10;
        pos.x += 2;
        Full_Color_Bitmap_Drawer::Draw(draw_list,pos,bitmap);
        
        
        
        /*
        ImGuiTreeNodeFlags flags = 0;
        if (ImGui::CollapsingHeader("Implementations", flags)){
            ImGui::Text("%s", "test");
        }
        if (ImGui::CollapsingHeader("Unit Tests", flags)){
            ImGui::Text("%s", "test");
        }
        if (ImGui::CollapsingHeader("Benchmarks", flags)){
            ImGui::Text("%s", "test");
        }
        */

    });
}


ide_settings get_ide_settings(){

    ide_settings settings;
    settings.init.main_window.title = "Unilang IDE";
    
    settings.tokens = Get_Tokens::Get();
    settings.unilang_font = Unilang_Font::Get();
    
    for (auto const& it: settings.unilang_font){
        settings.unilang_font_lookup[static_cast<int>(it.glyph_index)] = it;
    }
    
    settings.method_item.title              = "Function";
    settings.method_item.menu.title         = "Settings";
    settings.method_item.menu.shortcut      = "CTRL+F";
    settings.method_item.position.x         = 20;
    settings.method_item.position.y         = 38;
    settings.method_item.position.condition = ImGuiCond_Once;
    settings.method_item.size.width         = 800;
    settings.method_item.size.height        = 410;
    settings.method_item.size.condition     = ImGuiCond_Once;
    settings.method_item.titlebar           = false;
    settings.method_item.scrollbar          = true;
    settings.method_item.has_menu           = false;
    settings.method_item.move               = true;
    settings.method_item.resize             = true;
    settings.method_item.collapse           = true;
    settings.method_item.nav                = false;
    settings.method_item.close              = true;
    settings.method_item.is_open            = false;
    settings.method_item.focus              = false;
    settings.method_item.refocus_on_use     = false;
    settings.method_item.bg_alpha           = 1;
    
    return settings;
}


int main()
{
    auto s = get_ide_settings();
    
    auto before = [&](){
        
        //Initial Imgui styling
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowBorderSize = 0;
        style.WindowRounding = 0;
        
    };
    return Mechanics::render_each_frame(s.init,before,[&](){
        each_frame(s);
    });
}
