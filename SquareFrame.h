# include	<QtWidgets>
class SquareFrame : public QFrame
{
    Q_OBJECT

public:
    SquareFrame(QWidget* parent = NULL) : QFrame(parent)
    {
	QSizePolicy sizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred );
	sizePolicy.setHeightForWidth( true );
	this->setSizePolicy( sizePolicy );
    }

    virtual bool hasHeightForWidth() Q_DECL_OVERRIDE
    {
	return true;
    }

    virtual int heightForWidth(int w) const Q_DECL_OVERRIDE
    {
	return w;
    }
};
