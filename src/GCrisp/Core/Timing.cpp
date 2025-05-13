#include "Timing.h"
#include <iomanip>

namespace GCrisp {
void Timer::ProcessTime(ProcessedTime& elapsed,
                        const steady_clock::time_point& end) {
    GC_PROFILE_FUNC();
    elapsed.m_Time =
        duration_cast<microseconds>(end - m_Start).count() / 1000000.0f;
    m_Start = end;
}

ScopedTimer::~ScopedTimer() {
    m_Elapsed =
        duration_cast<microseconds>(steady_clock::now() - m_Start).count() /
        1000000.0f;
}

std::unordered_map<std::string, std::vector<ProfileResult>>
    TimingsProfiler::s_ProfilerMap =
        std::unordered_map<std::string, std::vector<ProfileResult>>();
char* TimingsProfiler::s_CurrentProfiler = (char*)calloc(0, sizeof(char));

ProfilerTimer::~ProfilerTimer() {
    m_Elapsed =
        duration_cast<microseconds>(steady_clock::now() - m_Start).count() /
        1000000.0f;

    TimingsProfiler::AddProfileResult(m_Result);
}

void TimingsProfiler::Init() { s_ProfilerMap.reserve(3); }

void TimingsProfiler::Shutdown() {
    for (auto& pair : s_ProfilerMap) {
        std::string profiler = pair.first;
        char filename[105];

        strncpy(filename, profiler.c_str(), 100);
        strncat(filename, ".json", 5);

        std::ofstream output(filename, std::ios::binary | std::ios::out);
        GC_CORE_VERIFY(output.is_open(),
                       "Could not open output {0} profiler file!", profiler);

        std::stringstream data;

        std::vector<ProfileResult>& results = s_ProfilerMap[profiler];

        data << std::setprecision(3) << std::fixed;

        data << "{\"otherData\": {},\"traceEvents\":[";

        GC_CORE_ASSERT(!results.empty(), "Results is empty!");
        size_t i = 0;
        for (auto& [Name, Thread, Elapsed, Start] : results) {
            data << "{\n";
            data << "\"cat\":\"function\",\n";
            data << "\"dur\":" << Elapsed.GetMicros() << ",\n";
            data << "\"name\":\"" << std::string(Name) << "\",\n";
            data << "\"ph\":\"X\",\n";
            data << "\"pid\":0,\n";
            data << "\"tid\":" << Thread << ",\n";
            data << "\"ts\":"
                 << std::chrono::duration<double, std::micro>(
                        Start.time_since_epoch())
                        .count();
            data << "}";
            if (i != results.size() - 1)
                data << ",";
            data << "\n";
            i++;
        }
        data << "]}";

        output.write(data.str().c_str(), data.str().size());
        output.close();

        results.clear();
        profiler.clear();
    }
    s_ProfilerMap.clear();
}

void TimingsProfiler::StartProfiler(const char* file) {
    // auto iter = s_ProfilerMap.find(file);
    // GC_CORE_VERIFY(iter == s_ProfilerMap.end(), "There is already a profiler
    // started with filename {0}!", file);
    auto vec = std::vector<ProfileResult>();
    vec.reserve(100);
    s_ProfilerMap[file] = vec;

    s_CurrentProfiler = (char*)calloc(100, sizeof(char));
    strncpy(s_CurrentProfiler, file, strlen(file));
    GC_CORE_INFO("Profiler {0}", s_CurrentProfiler);
}

void TimingsProfiler::EndProfiler() { free(s_CurrentProfiler); }

void TimingsProfiler::AddProfileResult(ProfileResult& result) {
    GC_CORE_ASSERT(s_CurrentProfiler, "Current profiler can't be null!");
    s_ProfilerMap[s_CurrentProfiler].emplace_back(result.Name, result.Thread,
                                                  result.Elapsed, result.Start);
}
} // namespace GCrisp
