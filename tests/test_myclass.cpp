// DataObjectTest.cpp
#include "Memory/DataObject.h"

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "Logger.h"

// Testuje konstruktor domyślny
TEST(DataObjectTest, DefaultConstructor)
{
    Memory::DataObject obj;
    EXPECT_NE(obj.GetData(), nullptr);
    EXPECT_EQ(obj.Size(), 0u);
    EXPECT_EQ(obj.GetData()->size(), 0u);
}

// Testuje konstruktor z shared_ptr
TEST(DataObjectTest, ConstructorWithData)
{
    auto data = std::make_shared<std::vector<char>>(100, 'a');
    Memory::DataObject obj(data);
    EXPECT_EQ(obj.GetData(), data);
    EXPECT_EQ(obj.Size(), 100u);
}

// Testuje SetData z poprawnymi danymi
TEST(DataObjectTest, SetDataValid)
{
    Memory::DataObject obj;
    auto data = std::make_shared<std::vector<char>>(50, 'b');
    size_t size = obj.SetData(std::move(data));
    EXPECT_EQ(size, 50u);
    EXPECT_EQ(obj.Size(), 50u);
    EXPECT_EQ(obj.GetData()->size(), 50u);
}

// Testuje SetData z null shared_ptr
TEST(DataObjectTest, SetDataNull)
{
    Memory::DataObject obj;
    std::shared_ptr<std::vector<char>> data = nullptr;
    size_t size = obj.SetData(std::move(data));
    EXPECT_EQ(size, 0u);
    EXPECT_EQ(obj.Size(), 0u);
    EXPECT_EQ(obj.GetData(), nullptr);
}

// Testuje metodę Allocate
TEST(DataObjectTest, Allocate)
{
    Memory::DataObject obj;
    obj.Allocate(200);
    EXPECT_NE(obj.GetData(), nullptr);
    EXPECT_EQ(obj.Size(), 200u);
    EXPECT_EQ(obj.GetData()->size(), 200u);
    // Sprawdza, czy wszystkie elementy są zainicjalizowane na '\0'
    for(auto c : *obj.GetData())
    {
        EXPECT_EQ(c, '\0');
    }
}

// Testuje Resize bez wymuszania
TEST(DataObjectTest, ResizeWithoutForce)
{
    auto data = std::make_shared<std::vector<char>>(100, 'c');
    Memory::DataObject obj(data);
    bool result = obj.Resize(80);
    EXPECT_FALSE(result); // Resize nie powinien się powieść
    EXPECT_EQ(obj.Size(), 100u);
    EXPECT_EQ(obj.GetData()->size(), 100u);
}

// Testuje Resize z wymuszeniem
TEST(DataObjectTest, ResizeWithForce)
{
    auto data = std::make_shared<std::vector<char>>(100, 'd');
    Memory::DataObject obj(data);
    bool result = obj.Resize(80, true);
    EXPECT_TRUE(result); // Resize powinien się powieść
    EXPECT_EQ(obj.Size(), 80u);
    EXPECT_EQ(obj.GetData()->size(), 80u);
}

// Testuje Resize na większy rozmiar
TEST(DataObjectTest, ResizeLarger)
{
    auto data = std::make_shared<std::vector<char>>(50, 'e');
    Memory::DataObject obj(data);
    bool result = obj.Resize(100);
    EXPECT_TRUE(result); // Resize powinien się powieść
    EXPECT_EQ(obj.Size(), 100u);
    EXPECT_EQ(obj.GetData()->size(), 100u);
}

// Testuje metodę Size
TEST(DataObjectTest, SizeMethod)
{
    Memory::DataObject obj;
    EXPECT_EQ(obj.Size(), 0u);

    obj.Allocate(10);
    EXPECT_EQ(obj.Size(), 10u);

    auto data = std::make_shared<std::vector<char>>(20, 'f');
    obj.SetData(std::move(data));
    EXPECT_EQ(obj.Size(), 20u);
}

// Testuje GetData gdy _data jest null
TEST(DataObjectTest, GetDataNull)
{
    Memory::DataObject obj;
    obj.SetData(nullptr);
    EXPECT_EQ(obj.GetData(), nullptr);
    EXPECT_EQ(obj.Size(), 0u);
}

// Testuje współdzielenie danych przez wiele instancji
TEST(DataObjectTest, SharedData)
{
    auto data = std::make_shared<std::vector<char>>(30, 'g');
    Memory::DataObject obj1(data);
    Memory::DataObject obj2 = obj1;
    EXPECT_EQ(obj1.GetData(), obj2.GetData());
    EXPECT_EQ(obj1.Size(), obj2.Size());

    // Modyfikuje dane przez obj1
    obj1.GetData()->at(0) = 'h';
    EXPECT_EQ(obj2.GetData()->at(0), 'h');
}

// Testuje Resize gdy _data jest początkowo null
TEST(DataObjectTest, ResizeWhenDataNull)
{
    Memory::DataObject obj;
    obj.SetData(nullptr);
    bool result = obj.Resize(25);
    EXPECT_TRUE(result);
    EXPECT_EQ(obj.Size(), 25u);
    EXPECT_EQ(obj.GetData()->size(), 25u);
}

int main(int argc, char **argv) {

    std::string path = "";
    Logger::InitLogger(path);

    auto logger = Logger::GetClassLogger("testClass");
    logger->info("Test loggera");

    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
