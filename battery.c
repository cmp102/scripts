#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <libnotify/notify.h>

const char* PWR_DIRNAME = "/sys/class/power_supply";
const int THRESHOLD = 10;

int main(){
	FILE *fCap, *fStatus;
	char filename[266], status[20];
	int cap;
	struct dirent *de;
	DIR *dr = opendir(PWR_DIRNAME);

	if(!dr){
		printf("ERROR, Cannot open: %s\n", PWR_DIRNAME);
		return 1;
	}

	while((de = readdir(dr))){

		//Discard some folders
		if(strcmp(de->d_name,".") == 0) continue;
		if(strcmp(de->d_name,"..") == 0) continue;

		//Capacity
		sprintf(filename, "%s/%s/capacity", PWR_DIRNAME, de->d_name);
		fCap = fopen(filename, "r");
		if(!fCap) continue;
		fscanf(fCap, "%d", &cap);
		fclose(fCap);

		//Status
		sprintf(filename, "%s/%s/status", PWR_DIRNAME, de->d_name);
		fStatus = fopen(filename, "r");
		if(!fStatus) continue;
		fscanf(fStatus, "%s", status);
		fclose(fStatus);

		if(strcmp(status, "Charging") == 0){
			printf("⚡%d\n", cap);
		}else{
			//If battery is discharging and to low
			if(cap <= THRESHOLD){
				char warningMsg[100];
				sprintf(warningMsg, "Battery low %d%%", cap);
				notify_init("warning");

				NotifyNotification* WarningNtf = notify_notification_new(
						"WARNING!",
						warningMsg,
						"dialog-information");

				notify_notification_set_urgency(
						WarningNtf,
						NOTIFY_URGENCY_CRITICAL);

				notify_notification_show (WarningNtf, NULL);
				g_object_unref(G_OBJECT(WarningNtf));
				notify_uninit();
			}
			printf("🔋%d\n", cap);
		}
	}

	closedir(dr);
}

