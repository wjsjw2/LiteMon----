#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

// 计算CPU使用率（核心函数）
double calculate_cpu_usage() {
    FILE* file = fopen("/proc/stat", "r");
    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

    unsigned long user, nice, system, idle;
    sscanf(line, "cpu  %lu %lu %lu %lu", &user, &nice, &system, &idle);
    
    unsigned long total = user + nice + system + idle;
    static unsigned long last_total = 0, last_idle = 0;
    double usage = 0.0;
    
    if (last_total > 0) { // 第二次之后计算差值
        unsigned long diff_total = total - last_total;
        unsigned long diff_idle = idle - last_idle;
        usage = 100.0 * (diff_total - diff_idle) / diff_total;
    }
    
    last_total = total;
    last_idle = idle;
    return usage;
}

int main() {
    // 获取内存信息
    struct sysinfo si;
    sysinfo(&si);
    double mem_usage = 100.0 * (si.totalram - si.freeram) / si.totalram;
    
    // 获取CPU使用率
    double cpu_usage = calculate_cpu_usage();
    
    // 写入日志文件
    FILE* log = fopen("system.log", "a");
    if (log != NULL) {
        fprintf(log, "%.2f,%.2f\n", cpu_usage, mem_usage);
        fclose(log);
    }
    return 0;
}





