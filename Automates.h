#ifndef AUTOMATES_H_INCLUDED
#define AUTOMATES_H_INCLUDED

class AutomateException {
private:
      std::string info;
public:
      AutomateException(const std::string& message):info(message) {}
      std::string getInfo() const { return info; }

};

#endif // AUTOMATES_H_INCLUDED
