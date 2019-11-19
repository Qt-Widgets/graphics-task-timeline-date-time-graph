TEMPLATE = subdirs

SUBDIRS = library \
          example

library.subdir  = graphics_library
example.subdir  = graphics_example

example.depends = library
