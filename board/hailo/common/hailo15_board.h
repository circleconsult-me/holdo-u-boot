#ifndef _HAILO15_BOARD_H
#define _HAILO15_BOARD_H

int hailo15_scmi_init(void);
int hailo15_scmi_check_version_match(void);
int hailo15_mmc_boot_partition(void);
int hailo15_get_active_boot_image_offset(void);

#endif /* _HAILO15_BOARD_H */