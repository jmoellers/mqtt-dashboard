# include       <iostream>
# include	"tile.h"
using namespace std;
extern int debug;

/*
 * NAME: tile
 * PURPOSE: Constructor for class tile
 * ARGUMENTS: _title: title to show at tope of tile
 *	_topic: topic to subscribe
 *	_unit: either a unit (eg "W" or "°") or a mapping value->text
 * RETURNS: Nothing
 */
tile::tile(QString _title, QString _topic, QString _unit, QSettings *settings)
{
    QFont largefont("OpenSans", 30);
    QRegularExpression opt(".*:.*(,.*:.*)*");

    mosqpp::lib_init();
    mosquittopp(NULL, true);

    host = settings->value("Host").toString();
    user = settings->value("Username").toString();
    pass = settings->value("Password").toString();
    port = settings->value("Port").toUInt();
    unit = _unit;
    topic = _topic;

    username_pw_set(user.toLocal8Bit().constData(), pass.toLocal8Bit().constData());
    mosqpp::mosquittopp::connect(host.toLocal8Bit().constData(), port);

    setFrameShadow(QFrame::Raised);
    setFrameShape(QFrame::Box);
    layout = new QVBoxLayout();

    // QSizePolicy sizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred );
    // sizePolicy.setHeightForWidth( true );
    // layout->setSizePolicy( sizePolicy );
    // layout->setGeometry(QRect(0, 0, 128, 128));

    title_label = new QLabel(_title);
    title_label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(title_label);
    if (opt.match(_unit).hasMatch())
    {
        QStringList opts = _unit.split(',');
	QStringList::const_iterator constIterator;
	for (constIterator = opts.constBegin(); constIterator != opts.constEnd();  ++constIterator)
	{
	    QStringList keyval = (*constIterator).split(':');
	    if (debug)
		cerr << (*constIterator).toLocal8Bit().constData() << endl;
	    options.insert(keyval.at(0), keyval.at(1));
	}
	value_label = new QLabel("");
	unit = QString("");
    }
    else
	value_label = new QLabel(_unit);
    value_label->setFont(largefont);
    value_label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(value_label);

    setLayout(layout);

    loop_start();
}

/*
 * NAME: ~tile
 * PURPOSE: Destructor of class tile
 * ARGUMENTS: None
 * RETURNS: Nothing
 */
tile::~tile()
{
    mosqpp::mosquittopp::disconnect();
    mosqpp::lib_cleanup();
}

/*
 * NAME: tile::on_connect
 * PURPOSE: To handle a CONNACK message from the broker
 * ARGUMENTS: res: result of connection, 0 -> OK
 * RETURNS: Nothing
 * NOTE: When the connection is established (res == 0),
 *	the topic is subscribed.
 */
void
tile::on_connect(int res)
{
    if (debug)
        cerr << "on_connect(res=" << res << ")\n";

    if (res != 0)
    {
        cerr << "connection refused\n";
        return;
    }

    // Subscribe to the topic of the object
    subscribe(NULL, topic.toUtf8().data());

    return;
}


/*
 * NAME: tile::on_message
 * PURPOSE: To handle an incoming message from the MQTT broker
 * ARGUMENTS: msg: the message data
 * RETURNS: Nothing
 * NOTE: This is a callback from the mosquitto library
 */
void
tile::on_message(const struct mosquitto_message *msg)
{
    if (debug)
        cerr << "on_message(" << msg->topic << "=>" << msg->payload << ")\n";

    QString s((char *) msg->payload);
    if (options.size() != 0)
        s = options[s];

    s += unit;
    // QFont f = value_label->font();
    // float factor = value_label->width() / QFontMetrics(f).width(s);
    // f.setPointSizeF(f.pointSizeF()*factor);
    // value_label->setFont(f);
    value_label->setText(s);
}
