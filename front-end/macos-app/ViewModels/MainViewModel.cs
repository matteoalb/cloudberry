using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;

namespace macos_app.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    private bool previewMode = false;
    private bool IsRawMode() => !previewMode;
    private bool IsPreviewMode() => previewMode;

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
    }

    [RelayCommand(CanExecute = nameof(IsRawMode))]
    private void Preview()
    {
        Console.WriteLine("Switched to preview mode");
        previewMode = true;
    }
}
