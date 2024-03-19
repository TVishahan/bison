#pragma once

#include <ux/gui.h>

int start_gui(){
    using namespace ftxui;
    auto screen_main = ScreenInteractive::Fullscreen();



    int menu_tab_index = 1;
    std::vector<std::string> menu_tab_entries = {
        " File ",
        " Scripts ",
        " Run ",
        " Logs ",
        " About "
    };
    auto menu_tab = Menu(&menu_tab_entries, &menu_tab_index,MenuOption::HorizontalAnimated());

    auto tab_file_btn_open = Button(" Open ", [&]{}, ButtonOption::Simple());
    auto tab_file_btn_save = Button(" Save ", [&]{}, ButtonOption::Simple());
    auto tab_file_btn_exit = Button(" Exit ", [&]{ screen_main.Exit(); }, ButtonOption::Simple());


    auto tab_component_file = Container::Horizontal({
        Container::Vertical({
            tab_file_btn_open,
            tab_file_btn_save,
            tab_file_btn_exit
        })
    });

    auto tab_renderer_file = Renderer(tab_component_file, [&] {
        return hbox({
            vbox({
                tab_file_btn_open->Render(),
                tab_file_btn_save->Render(),
                hbox() | flex_grow,
                tab_file_btn_exit->Render(),
            }) | size(WIDTH, EQUAL, 25),
            vbox({

            }) | size(WIDTH, EQUAL, 1),
            vbox({
                paragraph("Lorem ipsum dolor sit amet, consectetur adipiscing elit. In lacinia viverra convallis. Nullam vitae purus luctus, molestie diam ut, posuere lectus. Suspendisse potenti. Integer tellus nulla, fringilla vel mollis sed, congue et nibh. Vivamus tristique, neque sed sodales semper, dui nisl lacinia diam, viverra sollicitudin nulla quam eget justo. Vivamus sagittis velit nec ultricies sagittis. Aenean id libero ac felis volutpat molestie. Nam luctus neque eget neque hendrerit pharetra. Integer eu quam mi. Morbi et bibendum lorem."),
                text(""),
                paragraph("Nam rhoncus molestie dolor aliquet tempor. Pellentesque tincidunt sem in quam convallis, mattis interdum erat tristique. In eget tempus enim. Quisque id egestas risus. Donec efficitur mauris nibh, eget venenatis mi porta non. Cras sit amet orci orci. Pellentesque at luctus neque."),
                text(""),
                paragraph("Vestibulum finibus ligula molestie, venenatis arcu sed, sollicitudin dolor. Aliquam erat volutpat. Suspendisse ut imperdiet metus. Aenean pharetra dolor nec magna viverra placerat. Nulla nec sollicitudin neque. Vestibulum convallis vulputate semper. Morbi consectetur ultricies blandit. Mauris non dolor ullamcorper ligula maximus lacinia. Sed dignissim ipsum in faucibus volutpat. Praesent bibendum nibh et odio scelerisque gravida. Ut dui arcu, finibus sodales elementum eu, aliquam ut nisl. Nunc fringilla sapien ut luctus tempus.")
            })
        });
    });
    auto tab_renderer_scripts = Renderer([] {
        return vbox({
            text("All the cool script management stuff.")
        });
    });
    auto tab_renderer_run = Renderer([] {
        return vbox({
            text("Buttons and stuff to run the system.")
        });
    });
    auto tab_renderer_logs = Renderer([] {
        return vbox({
            text("Small browser to look at logs.")
        });
    });

    auto tab_renderer_about = Renderer([] {
        return vbox({
            text("Concept by Andrew Roth"),
            text("Implemented by Vishahan Thilagakumar")
        });
    });

    auto menu_tab_content = Container::Tab(
        {
            tab_renderer_file,
            tab_renderer_scripts,
            tab_renderer_run,
            tab_renderer_logs,
            tab_renderer_about,
        },
    &menu_tab_index);

    auto btn_close = Button("EXIT", [&]{}, ButtonOption::Ascii());
    auto container_main = Container::Vertical({
        btn_close,
        menu_tab,
        menu_tab_content
    });

    auto renderer_main = Renderer(container_main, [&]{
        return vbox({
            hbox({ 
                
                text("B I S O N") | bold | flex_grow,
                btn_close->Render()
            }),
            menu_tab->Render(),
            menu_tab_content->Render() | flex_grow
        });
    });

    
    screen_main.Loop(renderer_main);
    return 0;
}