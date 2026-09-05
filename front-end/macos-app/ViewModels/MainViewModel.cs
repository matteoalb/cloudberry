using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Avalonia.Media.Imaging;
using Avalonia.Platform;
using System;

namespace macos_app.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    private bool previewMode = true;
    private bool IsRawMode() => !previewMode;
    private bool IsPreviewMode() => previewMode;

    [ObservableProperty] private bool isPaneOpen;

    [ObservableProperty]
    private Bitmap? displayedImage;

    public MainViewModel()
    {
        DisplayedImage = LoadBitmap("avares://macos-app/Assets/blank_file.png");
    }


    [RelayCommand]
    private void Open()
    {
        Console.WriteLine("Opened file");
    }

    [RelayCommand]
    private void Download()
    {
        Console.WriteLine("Downloaded file");
    }

    [RelayCommand(CanExecute = nameof(IsPreviewMode))]
    private void Raw()
    {
        Console.WriteLine("Switched to raw mode");

        previewMode = false;
        RawCommand.NotifyCanExecuteChanged();
        PreviewCommand.NotifyCanExecuteChanged();

        DisplayedImage = LoadBitmap("avares://macos-app/Assets/blank_file.png");
    }

    [RelayCommand(CanExecute = nameof(IsRawMode))]
    private void Preview()
    {
        Console.WriteLine("Switched to preview mode");

        previewMode = true;
        RawCommand.NotifyCanExecuteChanged();
        PreviewCommand.NotifyCanExecuteChanged();

        Navigate(0);
    }

    [RelayCommand]
    private void TogglePane(){ IsPaneOpen = !IsPaneOpen; }

    [RelayCommand]
    private void LeftButton()
    {
        Navigate(-1);
    }

    [RelayCommand]
    private void RightButton()
    {
        Navigate(1);
    }

    private void Navigate(int input)
    {
        if(!previewMode)
            return;
    }

    private Bitmap LoadBitmap(string uri)
    {
        using var stream = AssetLoader.Open(new Uri(uri));
        return new Bitmap(stream);
    }
}
