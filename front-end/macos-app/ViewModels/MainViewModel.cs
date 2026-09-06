using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Avalonia.Media.Imaging;
using Avalonia.Platform;
using System;

using macos_app.Models;
using System.IO;

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
        LoadFile("");
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

    [RelayCommand]
    private void Delete()
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

        LoadFile("");
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

    public void LoadFile(string path)
    {
        if(path == "")
        {
            DisplayedImage = LoadBitmap("avares://macos-app/Assets/blank_file.png");
            return;
        }

        DisplayedImage = LoadBitmap(Path.Combine(HierarchyLoad.pathToRoot,path));
    }

    private Bitmap LoadBitmap(string path)
    {
        if (path.StartsWith("avares://"))
        {
            using var stream = AssetLoader.Open(new Uri(path));
            return new Bitmap(stream);
        }
        else
        {
            return new Bitmap(path);
        }
    }
}
