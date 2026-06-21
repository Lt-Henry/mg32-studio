
qt6_dep = dependency('qt6', modules: ['Core', 'Gui','Widgets'])
#moc_files = qt6.compile_moc(headers : ['bridge.hpp'], dependencies: qt6_dep)

compiler = meson.get_compiler('cpp')

executable('mg32-studio', ['editor.cpp','mainwindow.cpp','core.cpp','main.cpp'], dependencies: [qt6_dep], install: true)


