idf_component_register(
  SRCS "commands.c"
  INCLUDE_DIRS "include"
  PRIV_REQUIRES serial esp_timer esp_system
)
