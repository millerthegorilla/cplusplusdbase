#if !defined (ABOUT_H)
#define ABOUT_H
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Edit.h"

class AboutCtrl : public Dialog::ModalController
{
public:
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
private:
};

#endif
