//#include <ImageViewer.h>
//ImageViewer::ImageViewer()
//   : imageLabel(new QLabel)
//   , scrollArea(new QScrollArea)
//   , scaleFactor(1)
//{
//    imageLabel->setBackgroundRole(QPalette::Base);
//    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    imageLabel->setScaledContents(true);

//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setWidget(imageLabel);
//    scrollArea->setVisible(false);
//    setCentralWidget(scrollArea);

//    createActions();

//    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
//}
//static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
//{
//    static bool firstDialog = true;

//    if (firstDialog) {
//        firstDialog = false;
//        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
//        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
//    }

//    QStringList mimeTypeFilters;
//    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
//        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
//    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
//        mimeTypeFilters.append(mimeTypeName);
//    mimeTypeFilters.sort();
//    dialog.setMimeTypeFilters(mimeTypeFilters);
//    dialog.selectMimeTypeFilter("image/jpeg");
//    if (acceptMode == QFileDialog::AcceptSave)
//        dialog.setDefaultSuffix("jpg");
//}

//void ImageViewer::open()
//{
//    QFileDialog dialog(this, tr("Open File"));
//    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

//    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
//}
