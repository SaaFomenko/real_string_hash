#include <iostream>


static const char* p_fail_msg = "Set fail simple digit p.";
static const char* n_fail_msg = 
    "Set fail count n, this value can not equal null and "
    "must be 100 more than the number symbols in strings.";

class MyException : public std::exception
{
    private:
    const char* msg;

    public:
        MyException(const char* msg_) : msg(msg_){}
        virtual ~MyException(){}

        const char* what() const noexcept override
        {
            return msg;
        }
};

bool p_valid(int& p)
{
    bool isRemains = false;
    int rem = 0;
    if (p == 0) return isRemains;
    if (p < 0) p *= -1;
    if (p == 2) return true;

    for (int i = 2; i < p; ++i)
    {
        int rem = p % i;
//        std::cout << "Rem = " << rem << '\n';
        if (rem > 0) 
        {
            isRemains = true;
        }
        else
        {
            return isRemains;
        }
    }

//    std::cout << "isRem = " << isRemains;
    return isRemains;
}

bool n_valid(int& n, int size)
{
    if (n == 0) return false;
    if (n < 0) n *= -1;
    int limit_size = 100 * size;
    if (n <= limit_size) return false;

    return true;
}

unsigned int real_string_hash(std::string& str, int p, int n)
{
    const char* char_str = str.c_str();
    unsigned int size = str.length();
    unsigned int hash = 0;
    unsigned int i = 0;
    unsigned int mult = 1;

    if (!p_valid(p))
    {
        throw MyException(p_fail_msg);
    }
    if (!n_valid(n, size))
    {
        throw MyException(n_fail_msg);
    }

    while (char_str[i] != 0)
    {
        unsigned int code_char = static_cast<int>(char_str[i]);

        hash += static_cast<int>(char_str[i]) * mult;

        mult *= p;
        ++i;
    }

    hash = hash % n;
    return hash;
}

void clean_cin()
{
    if(char(std::cin.peek()) == '\n')
        std::cin.ignore();
    
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
}

//void quest_int_param(int& num, std::string& quest, )

int main(int argc, char const *argv[])
{
    const std::string n_error = 
        "Ошибка: n необходимо увеличить в 100 раз, "
        "для избежания колизий заначений xeшей для строк.";
    const std::string p_error = 
        "Ошибка: p должно быть более нуля и иметь остаток "
        "при делени на любое число кроме единици и самого себя.";
    const std::string p_lable = "Введите p: ";
    const std::string n_lable = "Введите n: ";
    const std::string quest = "Введите строку: ";
    const std::string response = "Хеш строки ";
    std::string str = "";
    std::string exit_str = "exit";
    unsigned int hash = 0;
    unsigned int exit_hash = 0;
    bool isValid = false;
    int p = 0;
    int n = 0;

    do
    {
        std::cout << p_lable;
        std::cin >> p;
        isValid = p_valid(p);
        
        if (!isValid)
        {
            std::cout << p_error << '\n';
        }
    } while (!isValid);

    do
    {
        if (n == 0)
        {
            std::cout << n_lable;
            std::cin >> n;

            clean_cin();

            try
            {                
                exit_hash = real_string_hash(exit_str, p, n);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }                        
        }

        std::cout << quest;
        std::getline(std::cin, str);

        int size = str.length();

        try
        {
            isValid = n_valid(n, size);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        while(!isValid)
        {
            std::cout << n_error << '\n';
            std::cout << n_lable;
            std::cin >> n;

            try
            {                
                isValid = n_valid(n, size);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            

            clean_cin();
            
            exit_hash = real_string_hash(exit_str, p, n);
        }

        hash = real_string_hash(str, p, n);

        std::cout << response << str << " = ";
        std::cout << hash << '\n';

    } while (hash != exit_hash);
    
    return 0;
}