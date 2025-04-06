#include <stdio.h>

int main() {
    int bucket_capacity, leak_rate, num_packets;

    printf("Enter the bucket capacity (bytes): ");
    scanf("%d", &bucket_capacity);

    printf("Enter the leak rate (bytes/unit): ");
    scanf("%d", &leak_rate);

    printf("Enter the number of packets: ");
    scanf("%d", &num_packets);

    int packets[num_packets];
    printf("Enter the size of each packet:\n");
    for (int i = 0; i < num_packets; i++) {
        printf("Packet[%d]: ", i + 1);
        scanf("%d", &packets[i]);
    }

    int bucket = 0;

    printf("\nLeaky Bucket Simulation:\n");
    printf("Incoming\tBucket\tLeaked\tRemaining\n");

    for (int i = 0; i < num_packets; i++) {
        int incoming = packets[i];

        // Ignore packets larger than bucket capacity
        if (incoming > bucket_capacity) {
            printf("%8d\tRejected (Too large)\n", incoming);
            continue;
        }

        // Fill bucket (only what fits)
        if (bucket + incoming > bucket_capacity) {
            incoming = bucket_capacity - bucket;
        }
        bucket += incoming;

        // Leak from bucket
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        int remaining = bucket - leaked;
        printf("%8d\t%6d\t%6d\t%8d\n", incoming, bucket, leaked, remaining);

        bucket = remaining;
    }

    // Drain the bucket after all packets are processed
    while (bucket > 0) {
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        int remaining = bucket - leaked;
        printf("%8d\t%6d\t%6d\t%8d\n", 0, bucket, leaked, remaining);
        bucket = remaining;
    }

    return 0;
}
