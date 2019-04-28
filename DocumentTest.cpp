#include "DocumentTest.h"

#include <string>
#include <list>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

void DocumentTest::testDocumentSize() {
	string json = "{\"data\":[{\"name\":-1100.1},{\"name\":\"Rose\"}]}";
	Document doc;
	doc.Parse<0>(json.c_str());
	//Value v(kArrayType);
	Value& v = doc["data"];
	cout << v.Size() << endl;
	int num = 10;
	Value value(10);
	cout << "Value: " << value.GetInt64() << endl;
	
	/*StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	v.Accept(writer);
	Value vv(buffer.GetString(),doc.GetAllocator());
	doc.AddMember("body",vv,doc.GetAllocator());
	
	StringBuffer buffer1;
	Writer<StringBuffer> writer1(buffer1);
	doc.Accept(writer1);
	cout << buffer1.GetString() << endl;*/
}

void DocumentTest::testValueType() {
	const string json = "{\"name\":\"Jack\",\"age\":1,\"is\":true,\"salary\":1.1}";
	Document doc;
	doc.Parse<0>(json.c_str());
	const char* attr = "name";
	if (doc.HasMember(attr)) {
		Value& v = doc[attr];
		cout << v.GetString() << endl;
	} else {
		cout << "Is null" << endl;
	}
	/*switch(v.Get()	) {
            case kNumberIntFlag:
            cout << "1" << endl;
                break;
            case kNumberInt64Flag:
            cout << "2" << endl;
                break;
            case kNumberDoubleFlag:
            cout << "3" << endl;
                break;
                default:
                cout << "default" << endl;
                break;
        }*/
}

//ͨ������һ��json�ַ�����������Document�У�Ȼ���ӡ��� 
void DocumentTest::testDocumentParse() {
	string json = "{\"metric_group\":{\"name\":\"impala-metrics\",\"metrics\":[{\"name\":\"impala-metric-1\",\"value\":1},{\"name\":\"impala-metric-2\",\"value\":2}],\"child_groups\":[{\"name\":\"impala-metrics-lchild\",\"metrics\":[{\"name\":\"impala-metrics-lchild-1\",\"value\":11},{\"name\":\"impala-metrics-lchild-2\",\"value\":12}],\"child_groups\":[]},{\"name\":\"impala-metrics-rchild\",\"metrics\":[{\"name\":\"impala-metrics-rchild-1\",\"value\":21},{\"name\":\"impala-metrics-rchild-2\",\"value\":22}],\"child_groups\":[]}]}}";
	Document doc;
	doc.Parse<0>(json.c_str());
	
	Value& value = doc["metric_group"];
	if (!value.ObjectEmpty())
		cout << "Not empty" << endl;
	cout << value.MemberCount() << endl;
		
	Value& vname = value["name"];
	cout << "Name: " << vname.GetString() << endl;

	const string name = vname.GetString();
	
	if (name == "impala-metrics")
		cout << "Equal" << endl;
	
	rapidjson::Value& vmetrics = value["metrics"];
	Value& m1 = vmetrics[0];

	Value& m1name = m1["name"];
	Value& m1value = m1["value"];
	cout << "m1: " << m1name.GetString() << "," << m1value.GetInt() << endl;
	
	rapidjson::Value& child_value = value["child_groups"];
	cout << "Count: " << child_value.Size() << endl;
	Value& child1 = child_value[0];
	Value& child1_metrics = child1["metrics"];
	cout << "child1_metrics: " << child1_metrics.Size() << endl;
	Value& child1_child = child1["child_groups"];
	cout << "child1_child: " << child1_child.Size() << endl;
	if (child1_child.Empty())
		cout << "Empty" << endl;
	
	/*
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	
	std::cout<< buffer.GetString() << std::endl;*/
}

//ΪDocument������Ӷ���Ȼ��һ���ӡ��� 
void DocumentTest::test2() {
	Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator();
	
	doc.AddMember("name", "Jack", allocator);
	doc.AddMember("age", 20, allocator);
	doc.AddMember("sex", "male", allocator);
	doc.AddMember("salary", 5000, allocator);
	
	std::string address = "Jiangnan Avenue.";
	Value aaa(address.c_str(), allocator); 
	doc.AddMember("address", aaa, allocator);
	
	Value& star = doc["age"];
	star.SetInt(star.GetInt()+1);
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	
	std::cout<< buffer.GetString() << std::endl;
}

//�������ͳ�Ա��ϴ���Document�У�Ȼ���ӡ��� 
void DocumentTest::test3() {
	Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator();
	
	//1.�����ַ�������
	doc.AddMember("author", "wangsheng", allocator);
	
	//2.�����������
	Value values(kArrayType);
	for(int i=0; i<3; i++) {
		Value int_obj(kObjectType);
		int_obj.SetInt(i);
		values.PushBack(int_obj, allocator);
	}
	doc.AddMember("number", values, allocator);
	
	//�����ַ����������
	Value str_values(kArrayType);
	Value str_obj1(kObjectType);
	const string s1 = "Java";
	str_obj1.SetString(s1.c_str(),s1.length());
    str_values.PushBack(str_obj1,allocator);
    
    Value str_obj2(kObjectType);
    const string s2 = "C++";
	str_obj2.SetString(s2.c_str(),s2.length());
    str_values.PushBack(str_obj2,allocator);
    doc.AddMember("string",str_values,allocator);
    
	
	//3.���Ӹ��϶���
	Value obj(kObjectType);
	obj.AddMember("language1", "C++", allocator);  
    obj.AddMember("language2", "Java", allocator);
    doc.AddMember("language", obj, allocator);
    
    //4.���Ӷ�������͸��϶�������
    Value valuess(kArrayType);
    Value object1(kObjectType);
    object1.AddMember("hobby","drawing",allocator);
    valuess.PushBack(object1, allocator);
    Value object2(kObjectType);
    object2.AddMember("height",1.71,allocator);
    valuess.PushBack(object2, allocator);
    doc.AddMember("information",valuess,allocator); 
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	
	std::cout<< buffer.GetString() << std::endl; 	
}

void DocumentTest::testList() {
	list<string> myList;
	myList.insert(myList.begin(),"first");
	//myList.insert(myList.begin(),"second");
	//myList.insert(myList.begin(),"third");
	//myList.insert(myList.begin(),"fourth");
	//myList.insert(myList.begin(),"fifth");
	
	list<string>& alias = myList;
	
	list<string>::iterator ite = alias.begin();
	while(ite!=alias.end()){
		if((*ite) == "third") {
			alias.erase(ite);
			break;
		}	
		std::cout << *ite++ << "\n";	
	}
	cout << "------------------------------" << endl;
	ite = myList.begin();
	while(ite!=myList.end()){
		std::cout << *ite++ << "\n";
	}
/*	
	list<string>::reverse_iterator rite = myList.rbegin();
	while(rite!=myList.rend()){
		std::cout << *rite << "\n";
		myList.erase(--(rite.base()));
	}

	list<string>::reverse_iterator rite;
	for (rite=myList.rbegin();rite!=myList.rend();rite++){
		std::cout << *rite << "\n";
	}*/
	
	if (myList.size() == 0)
		cout << "List is null now!\n";
	else
		cout << "List is not null!\n";
}

void DocumentTest::testString() {
	const string& head = "http://";
	const string& hostname = "db-87.photo.163.org";
	uint32_t port = 65000;
	
	char sport[32];
	sprintf(sport,"%d",port);
	//std::ostringstream os;
	//os << port;
	
	string full = head + ":" + hostname + ":" + sport;
	const char* cfull = full.c_str();
	cout << cfull << " ";
}

void DocumentTest::testString(string& input) {
	input = input + "_new";
}

string DocumentTest::testDocument() {
	Document doc;
	doc.SetObject();
	map<string, int> infoMap;
	infoMap["3"] = 3;
	infoMap["5"] = 5;
	infoMap["1"] = 1;
	infoMap["7"] = 7;
	infoMap["4"] = 4;
	
	Value address(kArrayType);
	Value size(kArrayType);
	map<string, int>::iterator ite = infoMap.begin();
	while (ite != infoMap.end()) {
		Value v1(kObjectType);
		v1.SetString(ite->first.c_str(), ite->first.length());
		address.PushBack(v1, doc.GetAllocator());
		Value v2(kObjectType);
		v2.SetInt(ite->second);
		size.PushBack(v2, doc.GetAllocator());
	    ite++;
	}
	
	doc.AddMember("address", address, doc.GetAllocator());
	doc.AddMember("size", size, doc.GetAllocator());
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	cout << buffer.GetString() << endl;
	return "";
}

void DocumentTest::testListIterator() {
	list<string> testList;
	if (testList.size() == 0) {
		cout << "List is null";
	} else {
		list<string>::iterator ite = testList.begin();
	while(ite != testList.end()) {
		std::cout << *ite++ << std::endl;
	}
	}
}

void DocumentTest::testStringToInteger() {
	string temp = "65537";
	int iTemp = atoi(temp.c_str());
	cout << iTemp << endl;
}

void DocumentTest::testDocumentValue() {
	string json = "{\"plan_nodes\":[{\"avg_time\":\"47.371ms\",\"broadcast\":false,\"children\":[{\"avg_time\":\"9.252us\",\"broadcast\":false,\"children\":[],\"label\":\"02:EXCHANGE\",\"label_detail\":\"UNPARTITIONED\",\"max_time\":\"9.252us\",\"max_time_val\":9252,\"num_instances\":1,\"output_card\":1,\"port\":0}],\"label\":\"03:AGGREGATE\",\"label_detail\":\"FINALIZE\",\"max_time\":\"47.371ms\",\"max_time_val\":47371919,\"num_instances\":1,\"output_card\":1,\"port\":0},{\"avg_time\":\"26.122ms\",\"broadcast\":false,\"children\":[{\"avg_time\":\"187.830ms\",\"broadcast\":false,\"children\":[],\"label\":\"00:SCAN HDFS\",\"label_detail\":\"wangs.student\",\"max_time\":\"187.830ms\",\"max_time_val\":187830359,\"num_instances\":1,\"output_card\":4,\"port\":0}],\"data_stream_target\":\"02:EXCHANGE\",\"label\":\"01:AGGREGATE\",\"label_detail\":\"\",\"max_time\":\"26.122ms\",\"max_time_val\":26122989,\"num_instances\":1,\"output_card\":1,\"port\":0}]}";
	Document docTemp;
	docTemp.Parse<0>(json.c_str());
	
	Document doc;
	doc.SetObject();
	//Value v(kArrayType);
	//v.AddMember(docTemp["student"], )
	Value v(kObjectType);
	v.AddMember("plan_nodes", docTemp["plan_nodes"], doc.GetAllocator());
	
	doc.AddMember("info", v, doc.GetAllocator());

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	cout<< buffer.GetString() << endl;
}

void DocumentTest::testClock() {
	double start, end;
	start = clock();
	for (int i=0; i<1000; i++)
		cout << i << endl;
	end = clock();
	cout << "Runtime: " << (end-start)/CLOCKS_PER_SEC << endl;
}

void DocumentTest::testValue() {
	Document doc;
	//doc.SetObject();
	string str = "{\"name\":\"Jack\",\"age\":24}";
	doc.Parse<0>(str.c_str());
	
	Document newDoc;
	newDoc.SetObject();
	rapidjson::Value v(doc["name"], newDoc.GetAllocator());
	newDoc.AddMember("nick", v, newDoc.GetAllocator());
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	cout << buffer.GetString() << endl;
}

void DocumentTest::TestArray() {
	string str = "{\"plan_nodes\":[{\"name\":\"node1\"},{\"name\":\"node2\"},{\"name\":\"node3\"}]}";
	//string str = "";
	Document tempDoc;
	tempDoc.Parse<0>(str.c_str());
	
	Document doc;
	doc.SetObject();
	if (!tempDoc.HasMember("plan_nodes")) {
		Value plan_nodes(kObjectType);
		plan_nodes.AddMember("plan_nodes", tempDoc["plan_nodes"], doc.GetAllocator());
		doc.AddMember("plan_json", plan_nodes, doc.GetAllocator());
	}
	
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::cout << buffer.GetString() << std::endl;
}