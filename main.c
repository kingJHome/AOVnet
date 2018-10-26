#include <stdio.h>
#include "aovnet.h"

int main(int argc,char *argv[]){
	FILE *fp = fopen("aovnet.txt","r");
	
	if( fp ){
		ALGraph algh = {NULL,0};

		//读文本内容，并构建有向图
		char head[3]="",tail[3]="",tips[4]="",content[50]="";
		while( fgets(content, 60, fp) ){
			sscanf(content, "%3s:%s %s\n", tips, head, tail);
			if( strcmp(tips,"Ver") == 0 ){
				char *temp = strchr(content,':') + 1;
				CreateALGraph(&algh, temp);
			}else if( strcmp(tips,"Arc") == 0 ){
				AddArcs(&algh, head, tail);
				break;
			}
			memset(content, '\0', 50);
		}
		//获取弧
		while( !feof(fp) && fscanf(fp, "%s %s\n", head, tail) ){
			AddArcs(&algh, head, tail);
		}

		fclose(fp);
		//拓扑排序
		if( TopologicalSort(algh) ){
			printf("排序完成，且不存在环!\n");
		}else{
			printf("存在环!\n");
		}
		clearALGraph(&algh);
	}
	return 0;
}
