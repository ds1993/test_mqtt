#include <mosquittopp.h>
#include <stdio.h>
#include <string.h>

static int run = -1;

class testmqtt: public mosqpp::mosquittopp {
public:
    testmqtt(const char* id);
    ~testmqtt();
    virtual void on_connect(int rc);
    virtual void on_disconnect(int rc);
    virtual void on_subscribe(int mid, int qos_count, const int* granted_qos);
    virtual void on_unsubscribe(int mid);
    virtual void on_publish(int mid);
};

testmqtt::testmqtt(const char* id): mosqpp::mosquittopp(id)
{
}

testmqtt::~testmqtt()
{
}

void testmqtt::on_connect(int rc)
{
    printf("testmqtt::%s, %d, rc = %d\n", __FUNCTION__, __LINE__, rc);
    if (rc != 0) {
        exit(1);
    }
    else {
        subscribe(NULL, "qos1/test", 1);
    }
}
void testmqtt::on_disconnect(int rc)
{
    printf("testmqtt::%s, %d, rc = %d\n", __FUNCTION__, __LINE__, rc);
    run = rc;
}

void testmqtt::on_subscribe(int mid, int qos_count, const int* granted_qos)
{
    printf("testmqtt::%s, %d, mid = %d, qos_count = %d, granted_qos = %d\n", __FUNCTION__, __LINE__, mid, qos_count, *granted_qos);
    publish(NULL, "qos1/test", strlen("message"), "message", 1, false);
}

void testmqtt::on_unsubscribe(int mid)
{
    printf("testmqtt::%s, %d, mid = %d\n", __FUNCTION__, __LINE__, mid);
    disconnect();
}

void testmqtt::on_publish(int mid)
{
    printf("testmqtt::%s, %d, mid = %d\n", __FUNCTION__, __LINE__, mid);
    unsubscribe(NULL, "qos1/test");
}

int main()
{
    testmqtt testMqtt("mytestpublish");
    mosqpp::lib_init();

    testMqtt.username_pw_set("admin", "111111");
    testMqtt.connect("127.0.0.1", 61613, 60);
    while (run == -1) {
        testMqtt.loop();
    }
    mosqpp::lib_cleanup();
    
    return 0;
}
