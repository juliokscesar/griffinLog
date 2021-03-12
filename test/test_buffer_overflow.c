#include <stdio.h>
#include <string.h>

#include "../Log.h"

int main()
{
    char *a = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In eu congue nisl. Aenean in nunc aliquam, tristique lectus eget, mollis neque. Cras eu lacus urna. Aenean eu quam non ex sollicitudin blandit eu a sapien. Fusce fermentum lacinia felis, eget mattis mi posuere ut. Vestibulum ultricies elit id ipsum lobortis condimentum. Vivamus sit amet ipsum faucibus, efficitur nunc ut, euismod ante. Nam eget felis mauris. Etiam quis mi ipsum. Nulla imperdiet egestas auctor. Nullam vitae purus sagittis, molestie ante ut, bibendum velit. Integer tempor tellus sit amet risus egestas condimentum non nec felis. Maecenas in faucibus tellus, vitae placerat ex. Phasellus ac faucibus neque. Sed eget enim ac tellus convallis porta at id mi. Nullam molestie rhoncus ipsum, lobortis accumsan mi facilisis in. Maecenas vulputate dignissim sem sit amet efficitur. Aliquam diam arcu, aliquet ut purus sit amet, rhoncus porta felis. Morbi cursus ultricies commodo. Duis quis urna non nunc finibus auctor. Cras ac porta turpis. Aenean arcu sapien, vehicula eget sapien suscipit, sagittis lobortis eit. Curabitur hendrerit aliquet sapien id dictum. Donec dictum nulla nunc, at porta est auctor et. Nullam molestie rhoncus ipsum, lobortis accumsan mi facilisis in. Maecenas vulputate dignissim sem sit amet efficitur. Aliquam diam arcu, aliquet ut purus sit amet, rhoncus porta felis. Morbi cursus ultricies commodo. Duis quis urna non nunc finibus auctor. Cras ac porta turpis. Aenean arcu sapien, vehicula eget sapien suscipit, sagittis lobortis elit. Curabitur hendrerit aliquet sapien id dictum. Donec dictum nulla nunc, at porta est auctor et. %s";
    printf("strlen(a) = %d\n", (int)strlen(a));

    LogInitCustom("buffer_overflow_log.log");
    LogInfo(a, "Nulla molestie ex nunc. Donec rhoncus magna non fringilla suscipit. Maecenas ut orci quis eros lacinia varius. Nulla pellentesque lacus vel risus mollis sagittis. Aliquam hendrerit at mi id vestibulum. Nunc sit amet feugiat mauris. Nunc scelerisque nunc a mattis auctor. Integer sed rhoncus risus. Phasellus non eros maximus, convallis felis in, sollicitudin nisl. Vestibulum lectus eros, finibus sit amet nulla vitae, imperdiet aliquam lorem.");
    LogFinish();

    return 0;
}