# include	<QtWidgets>
class SquareFrame : public QFrame
{
    Q_OBJECT

public:
    SquareFrame(QWidget* parent = NULL) : QFrame(parent)
    {
	QSizePolicy sizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding );
	// QSizePolicy sizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred );
	// QSizePolicy sizePolicy (QSizePolicy::Fixed, QSizePolicy::Preferred);
	sizePolicy.setHeightForWidth( true );
	this->setSizePolicy( sizePolicy );
	// useHeight = false;
    }

//    void useHeightForWidth(const bool &use){
//        useHeight = use;
//	if(use)
//	    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
//	else
//	    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
//    }

//    virtual bool hasHeightForWidth() Q_DECL_OVERRIDE
//    {
//	return true;
//    }

    virtual int heightForWidth(int w) const Q_DECL_OVERRIDE
    {
	return w;
    }

//protected:
//    virtual void resizeEvent(QResizeEvent *event)Q_DECL_OVERRIDE{
//	event->accept();
//	if(!useHeight){
//	    this->setMinimumWidth(this->height());
//	    this->setMaximumWidth(this->height());
//	}else{
//	    this->setMinimumHeight(this->width());
//	    this->setMaximumHeight(this->width());
//	}
//	updateGeometry();
//    }

//    bool useHeight; // = false;

};
